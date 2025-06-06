# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 2.8

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list

# Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The program to use to edit the cache.
CMAKE_EDIT_COMMAND = /usr/bin/ccmake

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /hpc/home/alessandro.dalpalu/gpu/matrixMul

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /hpc/home/alessandro.dalpalu/gpu/matrixMul/bin

# Include any dependencies generated for this target.
include CMakeFiles/matrixMul.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/matrixMul.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/matrixMul.dir/flags.make

CMakeFiles/matrixMul.dir/./matrixMul_generated_matrixMul.cu.o: ../matrixMul.cu
CMakeFiles/matrixMul.dir/./matrixMul_generated_matrixMul.cu.o: ../matrixMul.h
CMakeFiles/matrixMul.dir/./matrixMul_generated_matrixMul.cu.o: ../matrixMul_coalescing.cuh
CMakeFiles/matrixMul.dir/./matrixMul_generated_matrixMul.cu.o: ../matrixMul_compOpt.cuh
CMakeFiles/matrixMul.dir/./matrixMul_generated_matrixMul.cu.o: ../matrixMul_kernel.cuh
CMakeFiles/matrixMul.dir/./matrixMul_generated_matrixMul.cu.o: ../matrixMul_naive.cuh
CMakeFiles/matrixMul.dir/./matrixMul_generated_matrixMul.cu.o: ../matrixMul_noBankConflict.cuh
CMakeFiles/matrixMul.dir/./matrixMul_generated_matrixMul.cu.o: ../matrixMul_prefetch.cuh
CMakeFiles/matrixMul.dir/./matrixMul_generated_matrixMul.cu.o: ../matrixMul_tiling.cuh
CMakeFiles/matrixMul.dir/./matrixMul_generated_matrixMul.cu.o: ../matrixMul_unroll.cuh
CMakeFiles/matrixMul.dir/./matrixMul_generated_matrixMul.cu.o: /hpc/share/tools/cuda/10.2.89/include/builtin_types.h
CMakeFiles/matrixMul.dir/./matrixMul_generated_matrixMul.cu.o: /hpc/share/tools/cuda/10.2.89/include/channel_descriptor.h
CMakeFiles/matrixMul.dir/./matrixMul_generated_matrixMul.cu.o: /hpc/share/tools/cuda/10.2.89/include/crt/common_functions.h
CMakeFiles/matrixMul.dir/./matrixMul_generated_matrixMul.cu.o: /hpc/share/tools/cuda/10.2.89/include/crt/device_double_functions.h
CMakeFiles/matrixMul.dir/./matrixMul_generated_matrixMul.cu.o: /hpc/share/tools/cuda/10.2.89/include/crt/device_double_functions.hpp
CMakeFiles/matrixMul.dir/./matrixMul_generated_matrixMul.cu.o: /hpc/share/tools/cuda/10.2.89/include/crt/device_functions.h
CMakeFiles/matrixMul.dir/./matrixMul_generated_matrixMul.cu.o: /hpc/share/tools/cuda/10.2.89/include/crt/device_functions.hpp
CMakeFiles/matrixMul.dir/./matrixMul_generated_matrixMul.cu.o: /hpc/share/tools/cuda/10.2.89/include/crt/host_config.h
CMakeFiles/matrixMul.dir/./matrixMul_generated_matrixMul.cu.o: /hpc/share/tools/cuda/10.2.89/include/crt/host_defines.h
CMakeFiles/matrixMul.dir/./matrixMul_generated_matrixMul.cu.o: /hpc/share/tools/cuda/10.2.89/include/crt/math_functions.h
CMakeFiles/matrixMul.dir/./matrixMul_generated_matrixMul.cu.o: /hpc/share/tools/cuda/10.2.89/include/crt/math_functions.hpp
CMakeFiles/matrixMul.dir/./matrixMul_generated_matrixMul.cu.o: /hpc/share/tools/cuda/10.2.89/include/crt/sm_70_rt.h
CMakeFiles/matrixMul.dir/./matrixMul_generated_matrixMul.cu.o: /hpc/share/tools/cuda/10.2.89/include/crt/sm_70_rt.hpp
CMakeFiles/matrixMul.dir/./matrixMul_generated_matrixMul.cu.o: /hpc/share/tools/cuda/10.2.89/include/cuda_device_runtime_api.h
CMakeFiles/matrixMul.dir/./matrixMul_generated_matrixMul.cu.o: /hpc/share/tools/cuda/10.2.89/include/cuda_runtime.h
CMakeFiles/matrixMul.dir/./matrixMul_generated_matrixMul.cu.o: /hpc/share/tools/cuda/10.2.89/include/cuda_runtime_api.h
CMakeFiles/matrixMul.dir/./matrixMul_generated_matrixMul.cu.o: /hpc/share/tools/cuda/10.2.89/include/cuda_surface_types.h
CMakeFiles/matrixMul.dir/./matrixMul_generated_matrixMul.cu.o: /hpc/share/tools/cuda/10.2.89/include/cuda_texture_types.h
CMakeFiles/matrixMul.dir/./matrixMul_generated_matrixMul.cu.o: /hpc/share/tools/cuda/10.2.89/include/device_atomic_functions.h
CMakeFiles/matrixMul.dir/./matrixMul_generated_matrixMul.cu.o: /hpc/share/tools/cuda/10.2.89/include/device_atomic_functions.hpp
CMakeFiles/matrixMul.dir/./matrixMul_generated_matrixMul.cu.o: /hpc/share/tools/cuda/10.2.89/include/device_launch_parameters.h
CMakeFiles/matrixMul.dir/./matrixMul_generated_matrixMul.cu.o: /hpc/share/tools/cuda/10.2.89/include/device_types.h
CMakeFiles/matrixMul.dir/./matrixMul_generated_matrixMul.cu.o: /hpc/share/tools/cuda/10.2.89/include/driver_functions.h
CMakeFiles/matrixMul.dir/./matrixMul_generated_matrixMul.cu.o: /hpc/share/tools/cuda/10.2.89/include/driver_types.h
CMakeFiles/matrixMul.dir/./matrixMul_generated_matrixMul.cu.o: /hpc/share/tools/cuda/10.2.89/include/library_types.h
CMakeFiles/matrixMul.dir/./matrixMul_generated_matrixMul.cu.o: /hpc/share/tools/cuda/10.2.89/include/sm_20_atomic_functions.h
CMakeFiles/matrixMul.dir/./matrixMul_generated_matrixMul.cu.o: /hpc/share/tools/cuda/10.2.89/include/sm_20_atomic_functions.hpp
CMakeFiles/matrixMul.dir/./matrixMul_generated_matrixMul.cu.o: /hpc/share/tools/cuda/10.2.89/include/sm_20_intrinsics.h
CMakeFiles/matrixMul.dir/./matrixMul_generated_matrixMul.cu.o: /hpc/share/tools/cuda/10.2.89/include/sm_20_intrinsics.hpp
CMakeFiles/matrixMul.dir/./matrixMul_generated_matrixMul.cu.o: /hpc/share/tools/cuda/10.2.89/include/sm_30_intrinsics.h
CMakeFiles/matrixMul.dir/./matrixMul_generated_matrixMul.cu.o: /hpc/share/tools/cuda/10.2.89/include/sm_30_intrinsics.hpp
CMakeFiles/matrixMul.dir/./matrixMul_generated_matrixMul.cu.o: /hpc/share/tools/cuda/10.2.89/include/sm_32_atomic_functions.h
CMakeFiles/matrixMul.dir/./matrixMul_generated_matrixMul.cu.o: /hpc/share/tools/cuda/10.2.89/include/sm_32_atomic_functions.hpp
CMakeFiles/matrixMul.dir/./matrixMul_generated_matrixMul.cu.o: /hpc/share/tools/cuda/10.2.89/include/sm_32_intrinsics.h
CMakeFiles/matrixMul.dir/./matrixMul_generated_matrixMul.cu.o: /hpc/share/tools/cuda/10.2.89/include/sm_32_intrinsics.hpp
CMakeFiles/matrixMul.dir/./matrixMul_generated_matrixMul.cu.o: /hpc/share/tools/cuda/10.2.89/include/sm_35_atomic_functions.h
CMakeFiles/matrixMul.dir/./matrixMul_generated_matrixMul.cu.o: /hpc/share/tools/cuda/10.2.89/include/sm_35_intrinsics.h
CMakeFiles/matrixMul.dir/./matrixMul_generated_matrixMul.cu.o: /hpc/share/tools/cuda/10.2.89/include/sm_60_atomic_functions.h
CMakeFiles/matrixMul.dir/./matrixMul_generated_matrixMul.cu.o: /hpc/share/tools/cuda/10.2.89/include/sm_60_atomic_functions.hpp
CMakeFiles/matrixMul.dir/./matrixMul_generated_matrixMul.cu.o: /hpc/share/tools/cuda/10.2.89/include/sm_61_intrinsics.h
CMakeFiles/matrixMul.dir/./matrixMul_generated_matrixMul.cu.o: /hpc/share/tools/cuda/10.2.89/include/sm_61_intrinsics.hpp
CMakeFiles/matrixMul.dir/./matrixMul_generated_matrixMul.cu.o: /hpc/share/tools/cuda/10.2.89/include/surface_functions.h
CMakeFiles/matrixMul.dir/./matrixMul_generated_matrixMul.cu.o: /hpc/share/tools/cuda/10.2.89/include/surface_indirect_functions.h
CMakeFiles/matrixMul.dir/./matrixMul_generated_matrixMul.cu.o: /hpc/share/tools/cuda/10.2.89/include/surface_types.h
CMakeFiles/matrixMul.dir/./matrixMul_generated_matrixMul.cu.o: /hpc/share/tools/cuda/10.2.89/include/texture_fetch_functions.h
CMakeFiles/matrixMul.dir/./matrixMul_generated_matrixMul.cu.o: /hpc/share/tools/cuda/10.2.89/include/texture_indirect_functions.h
CMakeFiles/matrixMul.dir/./matrixMul_generated_matrixMul.cu.o: /hpc/share/tools/cuda/10.2.89/include/texture_types.h
CMakeFiles/matrixMul.dir/./matrixMul_generated_matrixMul.cu.o: /hpc/share/tools/cuda/10.2.89/include/vector_functions.h
CMakeFiles/matrixMul.dir/./matrixMul_generated_matrixMul.cu.o: /hpc/share/tools/cuda/10.2.89/include/vector_functions.hpp
CMakeFiles/matrixMul.dir/./matrixMul_generated_matrixMul.cu.o: /hpc/share/tools/cuda/10.2.89/include/vector_types.h
CMakeFiles/matrixMul.dir/./matrixMul_generated_matrixMul.cu.o: /usr/include/_G_config.h
CMakeFiles/matrixMul.dir/./matrixMul_generated_matrixMul.cu.o: /usr/include/alloca.h
CMakeFiles/matrixMul.dir/./matrixMul_generated_matrixMul.cu.o: /usr/include/assert.h
CMakeFiles/matrixMul.dir/./matrixMul_generated_matrixMul.cu.o: /usr/include/bits/byteswap-16.h
CMakeFiles/matrixMul.dir/./matrixMul_generated_matrixMul.cu.o: /usr/include/bits/byteswap.h
CMakeFiles/matrixMul.dir/./matrixMul_generated_matrixMul.cu.o: /usr/include/bits/endian.h
CMakeFiles/matrixMul.dir/./matrixMul_generated_matrixMul.cu.o: /usr/include/bits/huge_val.h
CMakeFiles/matrixMul.dir/./matrixMul_generated_matrixMul.cu.o: /usr/include/bits/huge_valf.h
CMakeFiles/matrixMul.dir/./matrixMul_generated_matrixMul.cu.o: /usr/include/bits/huge_vall.h
CMakeFiles/matrixMul.dir/./matrixMul_generated_matrixMul.cu.o: /usr/include/bits/inf.h
CMakeFiles/matrixMul.dir/./matrixMul_generated_matrixMul.cu.o: /usr/include/bits/local_lim.h
CMakeFiles/matrixMul.dir/./matrixMul_generated_matrixMul.cu.o: /usr/include/bits/mathcalls.h
CMakeFiles/matrixMul.dir/./matrixMul_generated_matrixMul.cu.o: /usr/include/bits/mathdef.h
CMakeFiles/matrixMul.dir/./matrixMul_generated_matrixMul.cu.o: /usr/include/bits/nan.h
CMakeFiles/matrixMul.dir/./matrixMul_generated_matrixMul.cu.o: /usr/include/bits/posix1_lim.h
CMakeFiles/matrixMul.dir/./matrixMul_generated_matrixMul.cu.o: /usr/include/bits/posix2_lim.h
CMakeFiles/matrixMul.dir/./matrixMul_generated_matrixMul.cu.o: /usr/include/bits/pthreadtypes.h
CMakeFiles/matrixMul.dir/./matrixMul_generated_matrixMul.cu.o: /usr/include/bits/select.h
CMakeFiles/matrixMul.dir/./matrixMul_generated_matrixMul.cu.o: /usr/include/bits/sigset.h
CMakeFiles/matrixMul.dir/./matrixMul_generated_matrixMul.cu.o: /usr/include/bits/stdio_lim.h
CMakeFiles/matrixMul.dir/./matrixMul_generated_matrixMul.cu.o: /usr/include/bits/stdlib-float.h
CMakeFiles/matrixMul.dir/./matrixMul_generated_matrixMul.cu.o: /usr/include/bits/sys_errlist.h
CMakeFiles/matrixMul.dir/./matrixMul_generated_matrixMul.cu.o: /usr/include/bits/time.h
CMakeFiles/matrixMul.dir/./matrixMul_generated_matrixMul.cu.o: /usr/include/bits/timex.h
CMakeFiles/matrixMul.dir/./matrixMul_generated_matrixMul.cu.o: /usr/include/bits/types.h
CMakeFiles/matrixMul.dir/./matrixMul_generated_matrixMul.cu.o: /usr/include/bits/typesizes.h
CMakeFiles/matrixMul.dir/./matrixMul_generated_matrixMul.cu.o: /usr/include/bits/waitflags.h
CMakeFiles/matrixMul.dir/./matrixMul_generated_matrixMul.cu.o: /usr/include/bits/waitstatus.h
CMakeFiles/matrixMul.dir/./matrixMul_generated_matrixMul.cu.o: /usr/include/bits/wordsize.h
CMakeFiles/matrixMul.dir/./matrixMul_generated_matrixMul.cu.o: /usr/include/bits/xopen_lim.h
CMakeFiles/matrixMul.dir/./matrixMul_generated_matrixMul.cu.o: /usr/include/c++/4.8.2/bits/atomic_lockfree_defines.h
CMakeFiles/matrixMul.dir/./matrixMul_generated_matrixMul.cu.o: /usr/include/c++/4.8.2/bits/cpp_type_traits.h
CMakeFiles/matrixMul.dir/./matrixMul_generated_matrixMul.cu.o: /usr/include/c++/4.8.2/cmath
CMakeFiles/matrixMul.dir/./matrixMul_generated_matrixMul.cu.o: /usr/include/c++/4.8.2/cstdlib
CMakeFiles/matrixMul.dir/./matrixMul_generated_matrixMul.cu.o: /usr/include/c++/4.8.2/exception
CMakeFiles/matrixMul.dir/./matrixMul_generated_matrixMul.cu.o: /usr/include/c++/4.8.2/ext/type_traits.h
CMakeFiles/matrixMul.dir/./matrixMul_generated_matrixMul.cu.o: /usr/include/c++/4.8.2/new
CMakeFiles/matrixMul.dir/./matrixMul_generated_matrixMul.cu.o: /usr/include/c++/4.8.2/x86_64-redhat-linux/bits/c++config.h
CMakeFiles/matrixMul.dir/./matrixMul_generated_matrixMul.cu.o: /usr/include/c++/4.8.2/x86_64-redhat-linux/bits/cpu_defines.h
CMakeFiles/matrixMul.dir/./matrixMul_generated_matrixMul.cu.o: /usr/include/c++/4.8.2/x86_64-redhat-linux/bits/os_defines.h
CMakeFiles/matrixMul.dir/./matrixMul_generated_matrixMul.cu.o: /usr/include/endian.h
CMakeFiles/matrixMul.dir/./matrixMul_generated_matrixMul.cu.o: /usr/include/features.h
CMakeFiles/matrixMul.dir/./matrixMul_generated_matrixMul.cu.o: /usr/include/gnu/stubs-64.h
CMakeFiles/matrixMul.dir/./matrixMul_generated_matrixMul.cu.o: /usr/include/gnu/stubs.h
CMakeFiles/matrixMul.dir/./matrixMul_generated_matrixMul.cu.o: /usr/include/libio.h
CMakeFiles/matrixMul.dir/./matrixMul_generated_matrixMul.cu.o: /usr/include/limits.h
CMakeFiles/matrixMul.dir/./matrixMul_generated_matrixMul.cu.o: /usr/include/linux/limits.h
CMakeFiles/matrixMul.dir/./matrixMul_generated_matrixMul.cu.o: /usr/include/math.h
CMakeFiles/matrixMul.dir/./matrixMul_generated_matrixMul.cu.o: /usr/include/stdc-predef.h
CMakeFiles/matrixMul.dir/./matrixMul_generated_matrixMul.cu.o: /usr/include/stdio.h
CMakeFiles/matrixMul.dir/./matrixMul_generated_matrixMul.cu.o: /usr/include/stdlib.h
CMakeFiles/matrixMul.dir/./matrixMul_generated_matrixMul.cu.o: /usr/include/string.h
CMakeFiles/matrixMul.dir/./matrixMul_generated_matrixMul.cu.o: /usr/include/sys/cdefs.h
CMakeFiles/matrixMul.dir/./matrixMul_generated_matrixMul.cu.o: /usr/include/sys/select.h
CMakeFiles/matrixMul.dir/./matrixMul_generated_matrixMul.cu.o: /usr/include/sys/sysmacros.h
CMakeFiles/matrixMul.dir/./matrixMul_generated_matrixMul.cu.o: /usr/include/sys/types.h
CMakeFiles/matrixMul.dir/./matrixMul_generated_matrixMul.cu.o: /usr/include/time.h
CMakeFiles/matrixMul.dir/./matrixMul_generated_matrixMul.cu.o: /usr/include/wchar.h
CMakeFiles/matrixMul.dir/./matrixMul_generated_matrixMul.cu.o: /usr/include/xlocale.h
CMakeFiles/matrixMul.dir/./matrixMul_generated_matrixMul.cu.o: /usr/lib/gcc/x86_64-redhat-linux/4.8.5/include/limits.h
CMakeFiles/matrixMul.dir/./matrixMul_generated_matrixMul.cu.o: /usr/lib/gcc/x86_64-redhat-linux/4.8.5/include/stdarg.h
CMakeFiles/matrixMul.dir/./matrixMul_generated_matrixMul.cu.o: /usr/lib/gcc/x86_64-redhat-linux/4.8.5/include/stddef.h
CMakeFiles/matrixMul.dir/./matrixMul_generated_matrixMul.cu.o: /usr/lib/gcc/x86_64-redhat-linux/4.8.5/include/syslimits.h
CMakeFiles/matrixMul.dir/./matrixMul_generated_matrixMul.cu.o: CMakeFiles/matrixMul.dir/matrixMul_generated_matrixMul.cu.o.cmake
CMakeFiles/matrixMul.dir/./matrixMul_generated_matrixMul.cu.o: ../matrixMul.cu
	$(CMAKE_COMMAND) -E cmake_progress_report /hpc/home/alessandro.dalpalu/gpu/matrixMul/bin/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold "Building NVCC (Device) object CMakeFiles/matrixMul.dir//./matrixMul_generated_matrixMul.cu.o"
	cd /hpc/home/alessandro.dalpalu/gpu/matrixMul/bin/CMakeFiles/matrixMul.dir && /usr/bin/cmake -E make_directory /hpc/home/alessandro.dalpalu/gpu/matrixMul/bin/CMakeFiles/matrixMul.dir//.
	cd /hpc/home/alessandro.dalpalu/gpu/matrixMul/bin/CMakeFiles/matrixMul.dir && /usr/bin/cmake -D verbose:BOOL=$(VERBOSE) -D build_configuration:STRING= -D generated_file:STRING=/hpc/home/alessandro.dalpalu/gpu/matrixMul/bin/CMakeFiles/matrixMul.dir//./matrixMul_generated_matrixMul.cu.o -D generated_cubin_file:STRING=/hpc/home/alessandro.dalpalu/gpu/matrixMul/bin/CMakeFiles/matrixMul.dir//./matrixMul_generated_matrixMul.cu.o.cubin.txt -P /hpc/home/alessandro.dalpalu/gpu/matrixMul/bin/CMakeFiles/matrixMul.dir//matrixMul_generated_matrixMul.cu.o.cmake

CMakeFiles/matrixMul.dir/matrixMul_gold.cpp.o: CMakeFiles/matrixMul.dir/flags.make
CMakeFiles/matrixMul.dir/matrixMul_gold.cpp.o: ../matrixMul_gold.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /hpc/home/alessandro.dalpalu/gpu/matrixMul/bin/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object CMakeFiles/matrixMul.dir/matrixMul_gold.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/matrixMul.dir/matrixMul_gold.cpp.o -c /hpc/home/alessandro.dalpalu/gpu/matrixMul/matrixMul_gold.cpp

CMakeFiles/matrixMul.dir/matrixMul_gold.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/matrixMul.dir/matrixMul_gold.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /hpc/home/alessandro.dalpalu/gpu/matrixMul/matrixMul_gold.cpp > CMakeFiles/matrixMul.dir/matrixMul_gold.cpp.i

CMakeFiles/matrixMul.dir/matrixMul_gold.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/matrixMul.dir/matrixMul_gold.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /hpc/home/alessandro.dalpalu/gpu/matrixMul/matrixMul_gold.cpp -o CMakeFiles/matrixMul.dir/matrixMul_gold.cpp.s

CMakeFiles/matrixMul.dir/matrixMul_gold.cpp.o.requires:
.PHONY : CMakeFiles/matrixMul.dir/matrixMul_gold.cpp.o.requires

CMakeFiles/matrixMul.dir/matrixMul_gold.cpp.o.provides: CMakeFiles/matrixMul.dir/matrixMul_gold.cpp.o.requires
	$(MAKE) -f CMakeFiles/matrixMul.dir/build.make CMakeFiles/matrixMul.dir/matrixMul_gold.cpp.o.provides.build
.PHONY : CMakeFiles/matrixMul.dir/matrixMul_gold.cpp.o.provides

CMakeFiles/matrixMul.dir/matrixMul_gold.cpp.o.provides.build: CMakeFiles/matrixMul.dir/matrixMul_gold.cpp.o

# Object files for target matrixMul
matrixMul_OBJECTS = \
"CMakeFiles/matrixMul.dir/matrixMul_gold.cpp.o"

# External object files for target matrixMul
matrixMul_EXTERNAL_OBJECTS = \
"/hpc/home/alessandro.dalpalu/gpu/matrixMul/bin/CMakeFiles/matrixMul.dir/./matrixMul_generated_matrixMul.cu.o"

matrixMul: CMakeFiles/matrixMul.dir/matrixMul_gold.cpp.o
matrixMul: CMakeFiles/matrixMul.dir/./matrixMul_generated_matrixMul.cu.o
matrixMul: CMakeFiles/matrixMul.dir/build.make
matrixMul: /hpc/share/tools/cuda/10.2.89/lib64/libcudart.so
matrixMul: CMakeFiles/matrixMul.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --red --bold "Linking C executable matrixMul"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/matrixMul.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/matrixMul.dir/build: matrixMul
.PHONY : CMakeFiles/matrixMul.dir/build

CMakeFiles/matrixMul.dir/requires: CMakeFiles/matrixMul.dir/matrixMul_gold.cpp.o.requires
.PHONY : CMakeFiles/matrixMul.dir/requires

CMakeFiles/matrixMul.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/matrixMul.dir/cmake_clean.cmake
.PHONY : CMakeFiles/matrixMul.dir/clean

CMakeFiles/matrixMul.dir/depend: CMakeFiles/matrixMul.dir/./matrixMul_generated_matrixMul.cu.o
	cd /hpc/home/alessandro.dalpalu/gpu/matrixMul/bin && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /hpc/home/alessandro.dalpalu/gpu/matrixMul /hpc/home/alessandro.dalpalu/gpu/matrixMul /hpc/home/alessandro.dalpalu/gpu/matrixMul/bin /hpc/home/alessandro.dalpalu/gpu/matrixMul/bin /hpc/home/alessandro.dalpalu/gpu/matrixMul/bin/CMakeFiles/matrixMul.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/matrixMul.dir/depend

