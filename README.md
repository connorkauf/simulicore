<a name="readme-top"></a>



## Table of contents

1. [About Compact Suite](#about-compact-suite)
2. [Build and Install](#build-and-install)
    - [Prerequisites](#prerequisites)
    - [Linux installation](#linux-installation)
    - [Windows installation](#windows-installation)
    - [Extra configuration arguments](#extra-configuration-arguments)
    - [Installation contents](#installation-contents)
3. [License](#license)
4. [Contact](#contact)




# About Compact Suite

**Compact Suite** is a collection of C++ libraries for scientific and computational development.

Traditional functional scientific programming is supported by a wide range of libraries and can be used for high performance code production, but at the same time it can be painful to master due to the vast documentation and the often long argument list of many of the APIs out there.

**Compact Suite** aims to bridge the gap between the established codebases and the modern object oriented coding style, while maintaining the efficiency, robustness and performance the first offers. 

The first library in the suite is [**CLA3P (Compact Linear Algebra Parallel Portable Package)**](cla3p.mod/README.md) a high performance linear algebra library that uses smart OOP design patterns and an intuitive API that allows the user to produce high quality code with minimum effort.

<p align="right">(<a href="#readme-top">back to top</a>)</p>




# Build and Install

To build and install the suite, follow these simple steps.

## Prerequisites

In order to build **Compact Suite** you will need:
* [CMake](https://cmake.org) 3.7.0 and above
* [GNU C++ compiler](https://gcc.gnu.org) (linux)
* [Microsoft Visual Studio](https://visualstudio.microsoft.com) (windows)
* [Intel Math Kernel Library](https://www.intel.com/content/www/us/en/developer/tools/oneapi/onemkl.html) (linux & windows) You can download it [here](https://www.intel.com/content/www/us/en/developer/tools/oneapi/onemkl-download.html).

## Linux Installation

1. Open the terminal
  
2. Clone the repo
   
   ```sh
   git clone git@github.com:connorkauf/CompactSuite.git
   cd CompactSuite
   ```
   
   For the purposes of this document, the top directory is marked as `<compact_suite_root>`.

3. Open file
   
   ```sh
   <compact_suite_root>/3rd/mkl.lin.cmake
   ```
   
   and set paths `MKL_ROOT` and `ICC_ROOT` to point to your installed copy of **Intel MKL** and **Intel Compiler** respectively.
   
   For more information, check this [Intel MKL Linking Guide](3rd/mkl.md).

   <a name="linux-cmake-config"></a>
4. Choose a build directory `build_dir` and use cmake command to configure the project
   
   ```sh
   cmake -S <compact_suite_root> -B <build_dir>
   ```
   
   For extra configuration options see section [Extra Configuration Arguments](#extra-configuration-arguments) further below.

5. Compile and install
    
   ```sh
   cmake --build <build_dir>
   cmake --install <build_dir>
   ```

## Windows Installation

1. Clone the repo using a cloning method of your choice
   
   ```sh
   https: https://github.com/connorkauf/CompactSuite.git
   ssh: git@github.com:connorkauf/CompactSuite.git
   ```
   
   For the purposes of this document, the top directory is marked as `<compact_suite_root>`.

2. Open file
   
   ```sh
   <compact_suite_root>/3rd/mkl.win.cmake
   ```
   
   and set paths `MKL_ROOT` and `ICC_ROOT` to point to your installed copy of **Intel MKL** and **Intel Compiler** respectively.

   For more information, check this [Intel MKL Linking Guide](3rd/mkl.md).

3. Start Microsoft Visual Studio and open the `compact_suite_root` directory.

   <a name="windows-cmake-config"></a>
4. Configure CMake from inside Microsoft Visual Studio (Project > CMake Settings for Compact Suite).
   
   For extra configuration options see section [Extra Configuration Arguments](#extra-configuration-arguments) further below.

5. Compile (Build > Build All)

6. Install (Build > Install Compact Suite)

## Extra configuration arguments

Below there is a list of configuration arguments for the entire project.  
For Linux append the desired options to the [Cmake Configuration](#linux-cmake-config).  
For Windows add the desired options in the section "CMake command arguments" in [CMake Settings](#windows-cmake-config).

#### <ins>Installation directory</ins>

The default installation directories are:  
`<compact_suite_root>/install` for Linux and  
`<compact_suite_root>/out/install/<build-type>` for Windows.  

You can specify an install directory by:

```
--install-prefix=<your_install_path>
```
or
```
-DCMAKE_INSTALL_PREFIX=<your_install_path>
```

#### <ins>Build CLA3P using 64bit integers</ins>

The default **CLA3P** integer length is 32bit.  
You can build **CLA3P** with 64bit integer length by:

```
-DCLA3P_USE_I64=true
```

## Installation contents

The default installation directories are:  
`<compact_suite_root>/install` for Linux and  
`<compact_suite_root>/out/install/<build-type>` for Windows.

In the installation directory you will find the following folders:
  
```
<compact_suite_install>/include : the compact suite include directory
<compact_suite_install>/lib     : the compact suite library directory
<compact_suite_install>/3rd     : directory containing the 3rd party library configurations
<compact_suite_install>/examples: the compact suite examples directory
```

<p align="right">(<a href="#readme-top">back to top</a>)</p>




# License

Distributed under the MIT License. See `LICENSE.txt` for more information.

<p align="right">(<a href="#readme-top">back to top</a>)</p>




# Contact

Connor Kaufman - connor.kaufman.gh@outlook.com  
Project Link: [https://github.com/connorkauf/CompactSuite](https://github.com/connorkauf/CompactSuite)  
Report an issue: [https://github.com/connorkauf/CompactSuite/issues](https://github.com/connorkauf/CompactSuite/issues) 

<p align="right">(<a href="#readme-top">back to top</a>)</p>



