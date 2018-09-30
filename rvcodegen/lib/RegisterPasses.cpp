//===--- RegisterPasses.cpp - Add the required passes to default passes  --===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
/// \file
/// Registration of RVCodeGen passes in the tool chain.
///
//===----------------------------------------------------------------------===//

#include "RVCodeGen/RVCodeGenPass.h"

#include "llvm/IR/LegacyPassManager.h"
#include "llvm/Transforms/IPO/PassManagerBuilder.h"
#include "llvm/Transforms/Scalar.h"

#include "llvm/Support/Debug.h"
#define DEBUG_TYPE "rvcodegen"

using namespace rvcodegen;
using namespace llvm;

namespace rvcodegen {
static void registerRVCodeGenPassPass(const PassManagerBuilder &,
                                      legacy::PassManagerBase &PM) {
  // Add transformations that need to run before the pass
  //PM.add(createPromoteMemoryToRegisterPass()); //mem2reg
  PM.add(new RVCodeGenPass());
}

static RegisterStandardPasses
    RegisterRVCodeGenPassForClang(PassManagerBuilder::EP_ModuleOptimizerEarly,
                 registerRVCodeGenPassPass);
} // namespace rvcodegen

#undef DEBUG_TYPE // "rvcodegen"
