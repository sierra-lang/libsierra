# reference file: llvm/test/CMakeLists.txt

# Tell lit to auto-generate lit.site.cfg from the hand-written lit.site.cfg.in
# This makes user specific paths which are already known to cmake also
# available for lit.cfg without hardcoding them
configure_lit_site_cfg(
  ${CMAKE_CURRENT_SOURCE_DIR}/lit.site.cfg.in
  ${CMAKE_CURRENT_BINARY_DIR}/lit.site.cfg
  )

# The tests are run in the binary dir, this is also where the generate site.cfg
# can be found.
add_lit_testsuite(check-RVCodeGen "Running the RVCodeGen lit tests"
  ${CMAKE_CURRENT_BINARY_DIR}
    PARAMS RVCodeGen_site_config=${CMAKE_CURRENT_BINARY_DIR}/lit.site.cfg
  )
set_target_properties(check-RVCodeGen PROPERTIES FOLDER "Tests")

