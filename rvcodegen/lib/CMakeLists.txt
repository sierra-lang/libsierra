set(LLVM_NO_RTTI 1)

set(RVCodeGen_HEADER_FILES)
if (MSVC_IDE OR XCODE)
    file(GLOB_RECURSE RVCodeGen_HEADER_FILES "${RVCodeGen_SOURCE_DIR}/include/RVCodeGen/*.h")
endif ()

# add all source files of the project that should be linked together
add_RVCodeGen_library(RVCodeGen
  RVCodeGenPass.cpp
  RegisterPasses.cpp
)

# List external library dependencies that need to be linked to your library
# (see project/myproject level CMakelists to enforce that these libraries are found)

if (BUILD_SHARED_LIBS)
  target_link_libraries(RVCodeGen
    LLVMSupport
    LLVMCore
    LLVMTransformUtils
    LLVMAnalysis
    LLVMipo
    LLVMMC
    RV
  )
  link_directories(
    ${LLVM_LIBRARY_DIR}
  )
endif()

link_directories(
  ${LLVM_LIBRARY_DIR}
)

# Build a monolithic RVCodeGen.a and a thin module LLVMRVCodeGen.moduleext that links to
# that static library.
if (MSVC)
  # Add dummy target, because loadable modules are not supported on Windows
  add_custom_target(LLVMRVCodeGen)
  set_target_properties(LLVMRVCodeGen PROPERTIES FOLDER "RVCodeGen")
else ()
  # Specify the files clang needs for the pass manager
  add_RVCodeGen_loadable_module(LLVMRVCodeGen
    RVCodeGenPass.cpp
    RegisterPasses.cpp
  )

  target_link_libraries(LLVMRVCodeGen RVCodeGen)

  set_target_properties(LLVMRVCodeGen
    PROPERTIES
    LINKER_LANGUAGE CXX
    PREFIX "")
endif ()

if (TARGET intrinsics_gen)
  # Check if we are building as part of an LLVM build
  add_dependencies(RVCodeGen intrinsics_gen)
endif()

