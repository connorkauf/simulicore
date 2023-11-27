# Compact Suite Installation Guide

Before continuing with installation, check the [Prerequisites](README.md#prerequisites) section.

## Table of contents

1. [Linux installation](#linux-installation)
2. [Windows installation](#windows-installation)
3. [Extra configuration arguments](#extra-configuration-arguments)




## Linux Installation

1. Open the terminal
  
2. Clone the repo
   
   ``` sh
   git clone git@github.com:connorkauf/CompactSuite.git
   cd CompactSuite
   ```
   
   For the purposes of this document, the top directory is marked as `<compact_suite_root>`.

3. Open file
   
   ``` sh
   <compact_suite_root>/3rd/mkl.lin.cmake
   ```
   
   and set paths `MKL_ROOT` and `ICC_ROOT` to point to your installed copy of **Intel&reg; MKL** and **Intel&reg; Compiler** respectively.
   
   For more information, check this [Intel&reg; MKL Linking Guide](3rd/mkl.md).

   <a name="linux-cmake-config"></a>
4. Choose a build directory `build_dir` and use cmake command to configure the project
   
   ``` sh
   cmake -S <compact_suite_root> -B <build_dir>
   ```
   
   For extra configuration options see section [Extra Configuration Arguments](#extra-configuration-arguments) further below.

5. Compile and install
    
   ``` sh
   cmake --build <build_dir>
   cmake --install <build_dir>
   ```




## Windows Installation

1. Clone the repo using a cloning method of your choice
   
   ``` sh
   https: https://github.com/connorkauf/CompactSuite.git
   ssh: git@github.com:connorkauf/CompactSuite.git
   ```
   
   For the purposes of this document, the top directory is marked as `<compact_suite_root>`.

2. Open file
   
   ``` sh
   <compact_suite_root>/3rd/mkl.win.cmake
   ```
   
   and set paths `MKL_ROOT` and `ICC_ROOT` to point to your installed copy of **Intel&reg; MKL** and **Intel&reg; Compiler** respectively.

   For more information, check this [Intel&reg; MKL Linking Guide](3rd/mkl.md).

3. Start Microsoft Visual Studio and open the `compact_suite_root` directory.

   <a name="windows-cmake-config"></a>
4. Configure CMake from inside Microsoft Visual Studio (Project > CMake Settings for Compact Suite).
   
   For extra configuration options see section [Extra Configuration Arguments](#extra-configuration-arguments) further below.

5. Compile (Build > Build All)

6. Install (Build > Install Compact Suite)




## Extra configuration arguments

Below there is a list of configuration arguments for the entire project.  
For Linux append the desired options to the [CMake Configuration](#linux-cmake-config).  
For Windows add the desired options in the section "CMake command arguments" in [CMake Settings](#windows-cmake-config).

#### <ins>Installation directory</ins>

The default installation directories are:  
`<compact_suite_root>/install` for Linux and  
`<compact_suite_root>/out/install/<build-type>` for Windows.  

You can specify an install directory by:

``` cmake
--install-prefix=<your_install_path>
```
or
``` cmake
-DCMAKE_INSTALL_PREFIX=<your_install_path>
```



