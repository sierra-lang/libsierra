#ifndef RVCodeGen_RVCodeGenPass_H
#define RVCodeGen_RVCodeGenPass_H

#include "llvm/IR/Module.h"
#include "llvm/Pass.h"

namespace llvm {
class PassRegistry;
void initializeRVCodeGenPassPass(PassRegistry &);
} // namespace llvm

namespace rv {
class VectorShape;
typedef std::vector<VectorShape> VectorShapeVec;
} // end namespace rv

namespace rvcodegen {

class RVCodeGenPass : public llvm::ModulePass {
public:
  static char ID;

  RVCodeGenPass();

  virtual bool doInitialization(llvm::Module &) override;

  virtual bool doFinalization(llvm::Module &) override;

  virtual bool runOnModule(llvm::Module & M) override;

  virtual void releaseMemory() override;

  virtual void getAnalysisUsage(llvm::AnalysisUsage & AU) const override;

  virtual void print(llvm::raw_ostream &, const llvm::Module *) const override;


  /********** private functions *****************/
//private: TODO comment in
  void createSimdFunction(llvm::Function *);

  void prepareFunctionForRV(llvm::Function *);

  unsigned fillShapesAndGetVecWidth(llvm::FunctionType *, llvm::FunctionType *,
                                    rv::VectorShape &, rv::VectorShapeVec &);

  void verify(llvm::Function *);

  void fixMaskInstructions(llvm::Function *, llvm::Value *);

};
} // namespace rvcodegen
#endif // RVCodeGen_RVCodeGenPass_H
