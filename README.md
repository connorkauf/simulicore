<a name="top"></a>



## Table of contents

1. [About SimuliCore](#about-simulicore)
2. [Build and Install](#build-and-install)
    - [Prerequisites](#prerequisites)
    - [Installation Guide](#installation-guide)
    - [Installation contents](#installation-contents)
3. [License](#license)
4. [Contact](#contact)




# About SimuliCore

**SimuliCore** is a collection of C++ libraries for scientific and computational development.

Traditional functional scientific programming is supported by a wide range of libraries and can be used for high performance code production, but at the same time it can be painful to master due to the vast documentation and the often long argument list of many of the APIs out there.

**SimuliCore** aims to bridge the gap between the established codebases and the modern object oriented coding style, while maintaining the efficiency, robustness and performance the first has to offer. 

The first library in the suite is [**CLA3P (Compact Linear Algebra Parallel Portable Package)**](cla3p.mod/README.md) a high performance linear algebra library that uses smart OOP design patterns and an intuitive API that allows the user to produce high quality code with minimum effort.

<p align="right">(<a href="#top">back to top</a>)</p>




# Build and Install

To build and install the suite, follow these simple steps.

## Prerequisites

In order to build **SimuliCore** you will need:
  * [CMake](https://cmake.org) 3.7.0 and above.
  * [Intel&reg; Math Kernel Library](https://www.intel.com/content/www/us/en/developer/tools/oneapi/onemkl.html) available for download [here](https://www.intel.com/content/www/us/en/developer/tools/oneapi/onemkl-download.html).

Development process default compilers are:
  * [GNU C++ compiler](https://gcc.gnu.org) v11.4.0
  * [Microsoft Visual Studio 2022](https://visualstudio.microsoft.com) msvc_x64 v17.8.2


## Installation Guide

For the **SimuliCore** installation guide see [INSTALL.md](INSTALL.md).

## Installation contents

The default installation directories are:  
`<simulicore_root>/install` for Linux and  
`<simulicore_root>/out/install/<build-type>` for Windows.

In the installation directory you will find the following folders:
  
```
<simulicore_install>/include : the SimuliCore include directory
<simulicore_install>/lib     : the SimuliCore library directory
<simulicore_install>/3rd     : directory containing the 3rd party library configurations
<simulicore_install>/examples: the SimuliCore examples directory
<simulicore_install>/license : licensing related documents
```

<p align="right">(<a href="#top">back to top</a>)</p>




# License

Licensed under the [Apache License, Version 2.0](https://www.apache.org/licenses/LICENSE-2.0). See [license](LICENSE) and [notice](NOTICE) for more information.

<p align="right">(<a href="#top">back to top</a>)</p>




# Contact

<picture><img alt="envelope" src="docs/images/icons-color/envelope.png" height=24px width=24px align="top"></picture> connor.kaufman.gh@outlook.com

<picture><img alt="bug" src="docs/images/icons-color/bug.png" height=24px width=24px align="top"></picture> [https://github.com/connorkauf/simulicore/issues](https://github.com/connorkauf/simulicore/issues)

<p align="right">(<a href="#top">back to top</a>)</p>



