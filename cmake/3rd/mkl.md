## About Intel&reg; MKL linking (x86_64 architectures)

Some modules of this project will depend on **Intel&reg; Math Kernel Library** in order to accelerate calculations. For example, if a project needs to use **CLA3P** it needs to be linked not only with **CLA3P** but with **Intel&reg; MKL** as well.  

Before compiling **SimuliCore** you need to edit file `mkl.lin.cmake` and/or `mkl.win.cmake` and set the CMake variables `INTEL_MKL_ROOT` and `INTEL_ICC_ROOT` to point to your installed copy of **Intel&reg; MKL** and **Intel&reg; Compiler** respectively.  

In these files, a standard setup of custom CMake variables is performed in order to make the compilation and linking process easier. The default configuration is dynamic linking using **Intel&reg; openMP** as threading layer. You can edit these files to create your own configuration if, for example, you want to link statically with **Intel&reg; MKL** libraries, or to use **GNU openMP** instead of **Intel&reg; openMP**. Consider visiting [**Intel&reg; MKL Link Line Advisor**](https://www.intel.com/content/www/us/en/developer/tools/oneapi/onemkl-link-line-advisor.html) for creating the setup that fits your needs.

After **SimuliCore** is installed, a copy of the edited files `mkl.lin.cmake` and `mkl.win.cmake` will be available in the `<simulicore_install>/cmake/3rd` directory. You can use these configuration files to build your own project using CMake.  

In order to generate the MKL CMake variables you can just include the appropriate file in your CMakeLists.txt
```cmake
if(${CMAKE_SYSTEM_NAME} STREQUAL "Windows")
  include(<simulicore_install>/cmake/3rd/mkl.win.cmake)
elseif(${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
  include(<simulicore_install>/cmake/3rd/mkl.lin.cmake)
endif()

message(STATUS "IntelMKL include dir: ${INTEL_MKL_INC}")
message(STATUS "IntelMKL lib list (32bit ints): ${INTEL_MKL_LIB}")
message(STATUS "IntelMKL lib list (64bit ints): ${INTEL_MKL_I64_LIB}")
```
This sets the `INTEL_MKL_<...>` and `INTEL_MKL_I64_<...>` variables to be used.

> <b><i>NOTE:</i></b>  
> **INTEL_MKL_LIB** is the library list needed for building applications using 32bit integers.  
> **INTEL_MKL_I64_LIB** is the library list needed for building applications using 64bit integers.  
> Select only one library list per target.  
> **INTEL_MKL_DEF** is the compile definitions list for complex number definitions & 32bit integers.  
> **INTEL_MKL_I64_DEF** is the compile definitions list for complex number definitions & 64bit integers (includes MKL_ILP64 definition).  

You can add the **Intel&reg; MKL** include directory to your CMake target with:
```cmake
target_include_directories(<target> PRIVATE ${INTEL_MKL_INC})
```

You can link your CMake target with **Intel&reg; MKL** in the following ways:
```cmake
#
# For 32bit integer lengths
#
target_link_libraries(<target> ${INTEL_MKL_LIB})

#
# For 64bit integer lengths
#
target_compile_definitions(<target> PRIVATE MKL_ILP64)
target_link_libraries(<target> ${INTEL_MKL_I64_LIB})
```

Below is the complete list of the CMake variables that are set in the `mkl.<os>.cmake`:
1) **INTEL_MKL_ROOT** (top Intel&reg; MKL directory)
2) **INTEL_ICC_ROOT** (top Intel&reg; Compiler directory)
3) **INTEL_MKL_DEF** (compile definitions for lp64 & complex definitions)
4) **INTEL_MKL_I64_DEF** (compile definitions for ilp64 & complex definitions)
5) **INTEL_MKL_INC** (Intel&reg; MKL include directory)
6) **INTEL_MKL_LIB_DIR** (Intel&reg; MKL library directory)
7) **INTEL_MKL_DLL_DIR** (Intel&reg; MKL redist library directory, windows only)
8) **INTEL_ICC_LIB_DIR** (Intel&reg; Compiler library directory)
9) **INTEL_ICC_DLL_DIR** (Intel&reg; Compiler redist directory, windows only)
10) **INTEL_MKL_LIB** (Complete Intel&reg; MKL & Intel&reg; Compiler linkage, 32bit integers)
11) **INTEL_MKL_I64_LIB** (Complete Intel&reg; MKL & Intel&reg; Compiler linkage, 64bit integers)
