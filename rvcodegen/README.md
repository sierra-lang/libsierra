# RVCodeGen

## Description

TODO add description


## Installation

### 1. Setting up LLVM

Start in your project root folder. Clone the [LLVM sources](https://github.com/llvm-mirror/llvm) as `llvm`. Next, clone the [Clang sources](https://github.com/llvm-mirror/clang) into `llvm/tools`. Make sure to checkout the same version branch in both of these repositories.

### 2. Setting up RVCodeGen

Clone this repository into `llvm/projects`.

### 3. Building LLVM+Clang+RVCodeGen

Create a new folder `build` in your project root folder and `cd` into it. Create build files via `cmake` with the following command:

```
cmake -G <build tool> <additional flags> ../llvm/
```

where `<build tool>` is your preferred build tool (e.g. `"Unix Makefile"` or `Ninja`).
Interesting additional flags for development are:

  * `-DLLVM_ENABLE_ASSERTIONS=1` to enforce assertions in the code
  * `-DCMAKE_BUILD_TYPE=Debug` to enable a debug build for better error messages and debugging capabilities
  * `-DLLVM_PARALLEL_LINK_JOBS=<n>` to limit the number of concurrent link jobs to `<n>`. This should be rather low for systems with less than 8GB of RAM as linking `clang` can require considerable amounts of memory (especially when building a debug build)
  * `-DLLVM_TARGETS_TO_BUILD=X86` to reduce build time by building only the X86 backend

When the build files are generated, use your build system to build the project (e.g. by typing `make` or `ninja`). This might take a while.

### 4. Build Targets

This project defines additional build targets to use with the build system:

  * `check-RVCodeGen` to run the test suite
  * `RVCodeGen-update-format` to run `clangformat` on all `RVCodeGen` source files


