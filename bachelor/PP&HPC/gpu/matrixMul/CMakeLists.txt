cmake_minimum_required(VERSION 2.8.0)
project(matrixMul)

SET(CudaArch "-arch;sm_60" CACHE STRING "Cuda arch")
Message(STATUS "Using CudaArch: ${CudaArch}")

# for finding GLog
set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")

find_package(CUDA REQUIRED)
include_directories(${CUDA_INCLUDE_DIRS})

IF(APPLE)
    include_directories(/System/Library/Frameworks)
ENDIF(APPLE)


set(GPU_SRC 
    matrixMul.cu
matrixMul_coalescing.cuh  matrixMul.cu        matrixMul_kernel.cuh  matrixMul_noBankConflict.cuh  matrixMul_tiling.cuh
matrixMul_compOpt.cuh     matrixMul_gold.cpp  matrixMul_naive.cuh   matrixMul_prefetch.cuh        matrixMul_unroll.cuh
    )

Message(STATUS "Using Arch: ${CudaArch}")
SET(CUDA_NVCC_FLAGS ${CudaArch})

cuda_add_executable(matrixMul ${GPU_SRC} OPTIONS -D__GPUVERSION__ -use_fast_math -Xptxas=-v -maxrregcount=50)
set_target_properties(matrixMul PROPERTIES COMPILE_FLAGS -D__GPUVERSION__)
set_target_properties(matrixMul PROPERTIES LINKER_LANGUAGE C)


SET(CMAKE_CXX_FLAGS "-Wall -Wno-unknown-pragmas -Wno-long-long -Wno-variadic-macros")
SET(CMAKE_CXX_FLAGS_RELEASE "-DNEXPENSIVE -g -O2 -g0")
SET(CMAKE_CXX_FLAGS_DEBUG "-DWARNINGS -O0 -g3 -fno-inline")

