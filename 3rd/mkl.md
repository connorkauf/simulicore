## About Intel&reg; MKL linking

Some modules of this project will depend on **Intel&reg; Math Kernel Library** in order to accelerate calculations. For example, if a project needs to use **CLA3P** it needs to be linked not only with **CLA3P** but with **Intel&reg; MKL** as well.  

Before compiling **SimuliCore** you need to edit file `mkl.lin.cmake` and/or `mkl.win.cmake` and set the CMake variables `MKL_ROOT` and `ICC_ROOT` to point to your installed copy of **Intel&reg; MKL** and **Intel&reg; Compiler** respectively.  

In these files, a standard setup of custom CMake variables is performed in order to make the compilation and linking process easier. The default configuration is dynamic linking using **Intel&reg; openMP** as threading layer. You can edit these files to create your own configuration if, for example, you want to link statically with **Intel&reg; MKL** libraries, or to use **GNU openMP** instead of **Intel&reg; openMP**. Consider visiting [**Intel&reg; MKL Link Line Advisor**](https://www.intel.com/content/www/us/en/developer/tools/oneapi/onemkl-link-line-advisor.html) for creating the setup that fits your needs.

After **SimuliCore** is installed, a copy of the edited files `mkl.lin.cmake` and `mkl.win.cmake` will be available in the `<simulicore_install>/3rd` directory. You can use these configuration files to build your own project using CMake.  

In order to generate the MKL CMake variables you can just include the appropriate file in your CMakeLists.txt
```cmake
if(WIN32)
  include(<simulicore_install>/3rd/mkl.win.cmake)
else()
  include(<simulicore_install>/3rd/mkl.lin.cmake)
endif()

message(STATUS "IntelMKL include dir: ${MKL_INC}")
message(STATUS "IntelMKL lib list (32bit ints): ${MKL_LIB}")
message(STATUS "IntelMKL lib list (64bit ints): ${MKL_I64_LIB}")
```
This sets the `MKL_INC`, `MKL_LIB` and `MKL_I64_LIB` variables to the MKL include directory and the MKL library dependencies respectively.

> **_NOTE:_**  
> **MKL_LIB** is the library list needed for building applications using 32bit integers.  
> **MKL_I64_LIB** is the library list needed for building applications using 64bit integers.  
> Select only one library list per target.  
> In the case of 64bit integers you will also need to add the MKL_ILP64 compile definition.

You can add the **Intel&reg; MKL** include directory to your CMake target with:
```cmake
target_include_directories(<target> PRIVATE ${MKL_INC})
```

You can link your CMake target with **Intel&reg; MKL** in the following ways:
```cmake
#
# For 32bit integer lengths
#
target_link_libraries(<target> ${MKL_LIB})

#
# For 64bit integer lengths
#
target_compile_definitions(<target> PRIVATE MKL_ILP64)
target_link_libraries(<target> ${MKL_I64_LIB})
```

Below is the complete list of the CMake variables that are set in the `mkl.<os>.cmake`:
1) **MKL_ROOT** (top Intel&reg; MKL directory)
2) **ICC_ROOT** (top Intel&reg; Compiler directory)
3) **MKL_INC** (Intel&reg; MKL include directory)
4) **MKL_LIB_DIR** (Intel&reg; MKL library directory)
5) **MKL_DLL_DIR** (Intel&reg; MKL redist library directory, windows only)
6) **ICC_LIB_DIR** (Intel&reg; Compiler library directory)
7) **ICC_DLL_DIR** (Intel&reg; Compiler redist directory, windows only)
8) **MKL_LIB** (Complete Intel&reg; MKL & Intel&reg; Compiler linkage, 32bit integers)
9) **MKL_I64_LIB** (Complete Intel&reg; MKL & Intel&reg; Compiler linkage, 64bit integers)
