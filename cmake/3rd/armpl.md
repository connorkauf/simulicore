## About Arm Performance Libraries linking (arm64 architectures)

Some modules of this project will depend on **Arm Performance Libraries** in order to accelerate calculations. For example, if a project needs to use **CLA3P** it needs to be linked not only with **CLA3P** but with **Arm Performance Libraries** as well.  

Before compiling **SimuliCore** you need to edit file `armpl.mac.cmake` and set the CMake variables `ARMPL_ROOT` to point to your installed copy of **Arm Performance Libraries**.  

In these files, a standard setup of custom CMake variables is performed in order to make the compilation and linking process easier. The default configuration is dynamic linking using **OpenMP**. You can edit these files to create your own configuration if, for example, you want to link statically. Consider visiting [**Arm Performance Libraries Reference Guide**](https://developer.arm.com/documentation/101004/2404/General-information/Access-Arm-Performance-Libraries) for more information.

After **SimuliCore** is installed, a copy of the edited file(s) `armpl.mac.cmake` will be available in the `<simulicore_install>/cmake/3rd` directory. You can use these configuration files to build your own project using CMake.  

In order to generate the ArmPL CMake variables you can just include the appropriate file in your CMakeLists.txt
```cmake
if(APPLE)
  include(<simulicore_install>/cmake/3rd/armpl.mac.cmake)
endif()

message(STATUS "ArmPL include dir: ${ARMPL_INC}")
message(STATUS "ArmPL lib list (32bit ints): ${ARMPL_LIB}")
message(STATUS "ArmPL lib list (64bit ints): ${ARMPL_I64_LIB}")
```
This sets the `ARMPL_<...>` and `ARMPL_I64_<...>` variables to be used.

> <b><i>NOTE:</i></b>  
> **ARMPL_LIB** is the library list needed for building applications using 32bit integers.  
> **ARMPL_I64_LIB** is the library list needed for building applications using 64bit integers.  
> Select only one library list per target.  
> **ARMPL_DEF** is the compile definitions list for complex number definitions & 32bit integers.  
> **ARMPL_I64_DEF** is the compile definitions list for complex number definitions & 64bit integers (includes INTEGERP64 definition).  

You can add the **Arm Performance Libraries** include directory to your CMake target with:
```cmake
target_include_directories(<target> PRIVATE ${ARMPL_INC})
```

You can link your CMake target with **Arm Performance Libraries** in the following ways:
```cmake
#
# For 32bit integer lengths
#
target_link_libraries(<target> ${ARMPL_LIB})

#
# For 64bit integer lengths
#
target_compile_definitions(<target> PRIVATE INTEGER64)
target_link_libraries(<target> ${ARMPL_I64_LIB})
```

Below is the complete list of the CMake variables that are set in the `armpl.<os>.cmake`:
1) **ARMPL_ROOT** (top Arm Performance Libraries directory)
2) **ARMPL_DEF** (compile definitions for lp64 & complex definitions)
3) **ARMPL_I64_DEF** (compile definitions for ilp64 & complex definitions)
4) **ARMPL_INC** (Arm Performance Libraries include directory)
5) **ARMPL_LIB_DIR** (Arm Performance Libraries library directory)
6) **ARMPL_LIB** (Complete Arm Performance Libraries linkage, 32bit integers)
7) **ARMPL_I64_LIB** (Complete Arm Performance Libraries linkage, 64bit integers)

<!-- 6) **ARMPL_DLL_DIR** (Arm Performance Libraries redist library directory, windows only) -->

