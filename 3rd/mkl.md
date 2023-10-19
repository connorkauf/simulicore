## About Intel MKL linking

Some modules of this project will depend on **Intel Math Kernel Library** in order to accelerate calculations. For example, if a project needs to use **CLA3P** it needs to be linked not only with **CLA3P** but with **Intel MKL** as well.  

Before compiling **Compact Suite** you need to edit file `mkl.lin.cmake` and/or `mkl.win.cmake` and set the CMake variables `MKL_ROOT` and `ICC_ROOT` to point to your installed copy of Intel MKL and Intel Compiler respectively.  

In these files, a standard setup of custom CMake variables is performed in order to make the compilation and linking process easier. The default configuration is dynamic linking using **Intel openMP** as threading layer. You can edit these files to create your own configuration if, for example, you want to link statically with **Intel MKL** libraries, or to use **GNU openMP** instead of **Intel openMP**. Consider visiting [**Intel MKL Link Line Advisor**](https://www.intel.com/content/www/us/en/developer/tools/oneapi/onemkl-link-line-advisor.html) for creating the setup that fits your needs.

After **Compact Suite** is installed, a copy of the edited files `mkl.lin.cmake` and `mkl.win.cmake` will be available in the `<compact_suite_install>/3rd` directory. You can use these configuration files to build your own project using CMake.  

In order to generate the MKL CMake variables you can just include the appropriate file in your CMakeLists.txt
```
if(WIN32)
  include("<compact_suite_install>/3rd/mkl.win.cmake")
else()
  include("<compact_suite_install>/3rd/mkl.lin.cmake")
endif()
```
This sets the `MKL_INC` and `MKL_LIB` variables to the MKL include directory and the MKL library dependencies respectively.

> **_NOTE:_**  
> Files mkl.lin.cmake and mkl.win.cmake use the CMake variable `CLA3P_USE_I64` to automatically determine which integer length to use. 
> Make sure to add `-DCLA3P_USE_I64=true` to your CMake configuration if you want **CLA3P** & **Intel MKL** to use 64bit integers.

If you want to include the **Intel MKL** include directory to your CMake target use:
```
target_include_directories(<target> PUBLIC ${MKL_INC})
```

In order to link your CMake target with **Intel MKL** use:
```
target_link_libraries(<target> ${MKL_LIB})
```

In order to link your CMake target with **CLA3P** that depends on **Intel MKL** use:
```
if(WIN32)
  set(CLA3P_LIB <compact_suite_install>/lib/cla3p.lib)
else()
  set(CLA3P_LIB -L<compact_suite_install>/lib -lcla3p)
endif()
target_link_libraries(<target> ${CLA3P_LIB} ${MKL_LIB})
```

Below is the complete list of the CMake variables that are set in the `mkl.<os>.cmake`:
1) **MKL_ROOT** (top Intel MKL directory)
2) **ICC_ROOT** (top Intel Compiler directory)
3) **MKL_INC** (Intel MKL include directory)
4) **MKL_LIB_DIR** (Intel MKL library directory)
5) **MKL_DLL_DIR** (Intel MKL redist library directory, windows only)
6) **ICC_LIB_DIR** (Intel Compiler library directory)
7) **ICC_DLL_DIR** (Intel Compiler redist directory, windows only)
8) **MKL_LIB** (Complete Intel MKL & Intel Compiler linkage)
