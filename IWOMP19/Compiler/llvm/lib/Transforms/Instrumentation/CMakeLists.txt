add_llvm_library(LLVMInstrumentation
  AddressSanitizer.cpp
  BoundsChecking.cpp
  DataFlowSanitizer.cpp
  GCOVProfiling.cpp
  MemorySanitizer.cpp
  IndirectCallPromotion.cpp
  Instrumentation.cpp
  InstrProfiling.cpp
  PGOInstrumentation.cpp
  SanitizerCoverage.cpp
  ThreadSanitizer.cpp
  EfficiencySanitizer.cpp
  Dependence_Analysis.cpp
  OMPCheckPass.cpp

  ADDITIONAL_HEADER_DIRS
  ${LLVM_MAIN_INCLUDE_DIR}/llvm/Transforms
  )

add_dependencies(LLVMInstrumentation intrinsics_gen)
