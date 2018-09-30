#include "RVCodeGen/RVCodeGenPass.h"

#include "clang/CodeGen/SierraMetadata.h"

#include "llvm/Analysis/LoopInfo.h"
#include "llvm/Analysis/MemoryDependenceAnalysis.h"
#include "llvm/Analysis/PostDominators.h"
#include "llvm/Analysis/ScalarEvolution.h"
#include "llvm/Analysis/TargetLibraryInfo.h"
#include "llvm/Analysis/TargetTransformInfo.h"
#include "llvm/IR/Dominators.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/IR/PassManager.h"
#include "llvm/IR/Verifier.h"
#include "llvm/Passes/PassBuilder.h"
#include "llvm/PassSupport.h"
#include "llvm/Support/CommandLine.h"
#include "llvm/Support/Debug.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/Transforms/Scalar.h"
#include "llvm/Transforms/Utils/Cloning.h"
#include "llvm/Transforms/Utils/ValueMapper.h"

#include "rv/analysis/DFG.h"
#include "rv/config.h"
#include "rv/passes.h"
#include "rv/PlatformInfo.h"
#include "rv/rv.h"
#include "rv/sleefLibrary.h"
#include "rv/transform/loopExitCanonicalizer.h"
#include "rv/vectorMapping.h"
#include "rv/vectorShape.h"

using namespace llvm;
using namespace rvcodegen;

#define DEBUG_TYPE "rvcodegen"

RVCodeGenPass::RVCodeGenPass() : ModulePass(ID) {}

bool RVCodeGenPass::doInitialization(Module &M) {
  return false;
}

bool RVCodeGenPass::doFinalization(Module &) {
  return false;
}

bool RVCodeGenPass::runOnModule(Module &M) {
  for (auto it = M.begin(); it != M.end(); ++it) {
    auto Func = &*it;
    if (rvcginstrument::hasVecInstrument(Func)) {
      DEBUG(dbgs() << "\n---------------------------\n\nVectorize "
                   << Func->getName().str() << "...\n");
      createSimdFunction(Func);
    }
  }
  return true;
}

void RVCodeGenPass::releaseMemory() {

}

void RVCodeGenPass::getAnalysisUsage(AnalysisUsage &AU) const {
  // add analysis passes that should be available during the pass run-time
}

void RVCodeGenPass::print(raw_ostream &/*OS*/, const Module * /*M*/) const {
  // TODO
}

void RVCodeGenPass::createSimdFunction(Function *Func) {
  if (verifyFunction(*Func, &errs())) {
    errs() << "Broken function " << Func->getName()
           << " found. It cannot be vectorized!\n";
    return;
  }
  auto Mod = Func->getParent();
  //auto &Ctx = Mod->getContext();
  std::string SimdFuncName = Func->getName().str() + "_SIMD";
  auto SimdFunc = Mod->getFunction(SimdFuncName);

  // verify functions and module
  if (!SimdFunc) {
    DEBUG(dbgs() << "Skip!\n");
    return;
  }
  //DEBUG(assert(SimdFunc && "No SimdFunc exists for the function"));
  //DEBUG(verify(Func));

  DEBUG(dbgs() << "Create SIMD function for " << Func->getName().str()
               << "...\n";);

  // position of the mask, < 0 means no mask
  int MaskPos = -1;
  if (rvcginstrument::hasMaskInstrument(Func)) {
    // position of the mask is always the last argument
    MaskPos = Func->getFunctionType()->getNumParams() - 1;
  }
  DEBUG(dbgs() << "Position of the mask is " << MaskPos << "\n");

  // call all needed optimization for rv on the function
  Function *OldFunc = Func;
  if (MaskPos >= 0) {
    Value *Mask = &*(--Func->arg_end());
    Type *Tmp = Mask->getType()->getVectorElementType();
    Value *TmpMask = new Argument(Tmp, "newMask");
    ValueToValueMapTy VMap;

    std::vector<Type*> ArgTypes;
    for (auto it = Func->arg_begin(); it != --Func->arg_end(); ++it)
      ArgTypes.push_back(it->getType());
    ArgTypes.push_back(Tmp);
    // Create a new function type...
    FunctionType *FTy =
        FunctionType::get(Func->getFunctionType()->getReturnType(), ArgTypes,
                          Func->getFunctionType()->isVarArg());
    // Create the new function...
    Function *NewFunc =
        Function::Create(FTy, Func->getLinkage(), Func->getName(), Mod);
    // Loop over the arguments, copying the names of the mapped arguments over...
    Function::arg_iterator DestI = NewFunc->arg_begin();
    for (auto it = Func->arg_begin(); it != --Func->arg_end(); ++it) {
      DestI->setName(it->getName()); // Copy the name over...
      VMap[&*it] = &*DestI++;        // Add mapping to VMap
    }
    DestI->setName(TmpMask->getName());
    VMap[Mask] = TmpMask;
    SmallVector<ReturnInst *, 8> Returns; // Ignore returns cloned.
    CloneFunctionInto(NewFunc, Func, VMap, Func->getSubprogram() != nullptr,
                      Returns, "", nullptr);
    fixMaskInstructions(NewFunc, TmpMask);
    Func = NewFunc;
  }
  if (verifyFunction(*Func, &errs())) {
    errs() << "Broken function " << Func->getName()
           << " found. It cannot be vectorized!\n";
    return;
  }

  prepareFunctionForRV(Func);

  // create shapes
  rv::VectorShape ResShape;
  rv::VectorShapeVec ArgShape;
  unsigned VecWidth = fillShapesAndGetVecWidth(
      Func->getFunctionType(), SimdFunc->getFunctionType(), ResShape, ArgShape);

  rv::VectorMapping VecJob(Func, SimdFunc, VecWidth, MaskPos, ResShape,
                           ArgShape);

  // create a temporary clone of the scalar function for transformation
  ValueToValueMapTy ValMap;
  Function *FuncCopy = CloneFunction(Func, ValMap, nullptr);
  DEBUG(assert(FuncCopy && "Sth went wrong when during coloning"));
  FuncCopy->setCallingConv(Func->getCallingConv());
  FuncCopy->setAttributes(Func->getAttributes());
  FuncCopy->setAlignment(Func->getAlignment());
  FuncCopy->setLinkage(GlobalValue::InternalLinkage);
  FuncCopy->setName(OldFunc->getName() + ".vectorizer.tmp");

  // call all needed optimization for rv on the function
  prepareFunctionForRV(FuncCopy);
  FunctionAnalysisManager FAM;
  ModuleAnalysisManager MAM;

  // setup LLVM analysis infrastructure
  PassBuilder PB;
  PB.registerFunctionAnalyses(FAM);
  PB.registerModuleAnalyses(MAM);

  // platform API
  TargetIRAnalysis IrAnalysis;
  TargetTransformInfo TTI = IrAnalysis.run(*FuncCopy, FAM);
  TargetLibraryAnalysis LibAnalysis;
  TargetLibraryInfo TLI = LibAnalysis.run(*FuncCopy->getParent(), MAM);
  rv::PlatformInfo PlatformInf(*Mod, &TTI, &TLI);

  // configure RV
  rv::Config Conf;
  Conf.useSLEEF = true;
  const bool UseImpreciseFunctions = true;
  DEBUG(Conf.print(dbgs()));

  // link in SIMD library
  addSleefMappings(Conf, PlatformInf, UseImpreciseFunctions);

  rv::VectorizerInterface Vectorizer(PlatformInf, Conf);

  // set-up VecInfo overlay and define vectorization job (mapping)
  rv::VectorMapping TargetMapping = VecJob;
  TargetMapping.scalarFn = FuncCopy;
  rv::VectorizationInfo VecInfo(TargetMapping);

  // build Analysis
  DominatorTree DomTree(*FuncCopy);
  // normalize loop exits
  {
    LoopInfo LoopInf(DomTree);
    LoopExitCanonicalizer Canonicalizer(LoopInf);
    Canonicalizer.canonicalize(*FuncCopy);
    DomTree.recalculate(*FuncCopy);
  }

  LoopInfo LoopInf(DomTree);

  ScalarEvolutionAnalysis SEAnalysis;
  ScalarEvolution SE = SEAnalysis.run(*FuncCopy, FAM);

  MemoryDependenceAnalysis MDAnalysis;
  MemoryDependenceResults MDR = MDAnalysis.run(*FuncCopy, FAM);

  // Dominance Frontier Graph
  DFG DomFG(DomTree);
  DomFG.create(*FuncCopy);

  // post dom
  PostDominatorTree PostDomTree;
  PostDomTree.recalculate(*FuncCopy);

  // Control Dependence Graph
  CDG CDepG(PostDomTree);
  CDepG.create(*FuncCopy);

  { // dump normalized function
    DEBUG(dbgs() << "-- normalized functions --\n");
    DEBUG(FuncCopy->print(dbgs()));
  }

  // early math func lowering
  Vectorizer.lowerRuntimeCalls(VecInfo, LoopInf);
  DomTree.recalculate(*FuncCopy);
  PostDomTree.recalculate(*FuncCopy);
  CDepG.create(*FuncCopy);
  DomFG.create(*FuncCopy);

  DEBUG(LoopInf.print(dbgs()));
  DEBUG(LoopInf.verify(DomTree));

  // vectorizationAnalysis
  Vectorizer.analyze(VecInfo, CDepG, DomFG, LoopInf);

  // mask generator
  Vectorizer.linearize(VecInfo, CDepG, DomFG, LoopInf, PostDomTree, DomTree);

  // Control conversion does not preserve the domTree so we have to rebuild it
  DominatorTree DomTreeNew(*VecInfo.getMapping().scalarFn);
  bool VecOk =
      Vectorizer.vectorize(VecInfo, DomTreeNew, LoopInf, SE, MDR, nullptr);
  DEBUG(assert(VecOk && "vector code generation failed"));

  DEBUG(dbgs() << "-- vectorized functions --\n");
  DEBUG(VecInfo.getMapping().vectorFn->print(dbgs()));

  // cleanup
  Vectorizer.finalize();

  FuncCopy->eraseFromParent();
  if (MaskPos > 0) {
    Func->eraseFromParent();
    Func = OldFunc;
  }
}

void RVCodeGenPass::prepareFunctionForRV(Function* F) {
  legacy::FunctionPassManager FPM(F->getParent());
  FPM.add(rv::createCNSPass());
  FPM.add(createPromoteMemoryToRegisterPass());
  FPM.add(createLoopSimplifyPass());
  FPM.add(createLCSSAPass());
  FPM.run(*F);

  // verify again that nothing broke
  //DEBUG(verify(F));
}

unsigned RVCodeGenPass::fillShapesAndGetVecWidth(FunctionType *FT,
                                                 FunctionType *VecFT,
                                                 rv::VectorShape &ResShape,
                                                 rv::VectorShapeVec &ArgShape) {
  DEBUG(dbgs() << "---> Creating VectorShapes from\n---> ");
  DEBUG(FT->print(dbgs()));
  DEBUG(dbgs() << " and\n---> ");
  DEBUG(VecFT->print(dbgs()));
  DEBUG(dbgs() << "\n");

  // ret of this method
  unsigned VecWidth = 1;

  // create ResShape
  auto ResFT = FT->getReturnType();
  auto ResVecFT = VecFT->getReturnType();
  //if (ResFT->isPointerTy() && ResVecFT->isPointerTy()) {
    //ResFT = ResFT->getPointerElementType();
    //ResVecFT = ResVecFT->getPointerElementType();
  //}
  if (ResVecFT->isVectorTy() && !ResFT->isVectorTy()) {
    DEBUG(dbgs() << "return will be varying\n");
    ResShape = rv::VectorShape::varying();
    VecWidth = ResVecFT->getVectorNumElements();
  } else {
    DEBUG(dbgs() << "return will be uniform\n");
    ResShape = rv::VectorShape::uni();
  }

  // create ArgShape
  // TODO mask
  for (unsigned i = 0; i < FT->getNumParams(); ++i) {
    auto ArgFT = FT->getParamType(i);
    auto ArgVecFT = VecFT->getParamType(i);
    //if (ArgFT->isPointerTy() && ArgVecFT->isPointerTy()) {
      //ArgFT = ArgFT->getPointerElementType();
      //ArgVecFT = ArgVecFT->getPointerElementType();
    //}
    if (ArgVecFT->isVectorTy() && !ArgFT->isVectorTy()) {
      DEBUG(dbgs() << "arg " << i << " will be varying\n");
      DEBUG(assert(VecWidth == 1 ? true : (VecWidth ==
                                           ArgVecFT->getVectorNumElements())));
      ArgShape.push_back(rv::VectorShape::varying());
      VecWidth = ArgVecFT->getVectorNumElements();
    } else {
      DEBUG(dbgs() << "arg " << i << " will be uniform\n");
      ArgShape.push_back(rv::VectorShape::uni());
    }
  }

  DEBUG(dbgs() << "vector width is " << VecWidth << "\n");
  return VecWidth;
}

void RVCodeGenPass::verify(Function *Func) {
  auto Mod = Func->getParent();
  assert(verifyModule(*Mod, &dbgs()) && "Broken module!");
  assert(verifyFunction(*Func, &dbgs()) && "Broken function!");
}

void RVCodeGenPass::fixMaskInstructions(Function *Func, Value *Mask) {
  //SmallVector<Value, 32> ToRemove;
  //for (auto it : Mask->users()) {
    //if (auto Inst = dyn_cast<Instruction>(it)) {
      //Inst->dump();
    //}
  //}
}



char RVCodeGenPass::ID = 0;

static RegisterPass<RVCodeGenPass>
    RegisterRVCodeGenPassForOpt("rvcodegen", "use when clang -fsierra is used",
                                false,  // CFGOnly
                                false); // isAnalysis


#undef DEBUG_TYPE // "rvcodegen"

//static RVCodeGenPass RVCodeGenPassInitializer;

//INITIALIZE_PASS_BEGIN(RVCodeGenPass,
                      //"rvcodegen",                       // cli identifier
                      //"use when clang -fsierra is used", // -help description
                      //false,                             // does not change cfg
                      //false)                             // is analysis
//// Transformations to be performed before this pass
//// INITIALIZE_PASS_DEPENDENCY(SomeWrapperPass)
//INITIALIZE_PASS_END(RVCodeGenPass,
                    //"rvcodegen",                       // cli identifier
                    //"use when clang -fsierra is used", // -help description
                    //false,                             // does not change cfg
                    //false)                             // is analysis
