<a name="top"></a>



## Table of contents

1. [About Compact Suite](#about-compact-suite)
2. [Build and Install](#build-and-install)
    - [Prerequisites](#prerequisites)
    - [Installation Guide](#installation-guide)
    - [Installation contents](#installation-contents)
3. [License](#license)
4. [Contact](#contact)




# About Compact Suite

**Compact Suite** is a collection of C++ libraries for scientific and computational development.

Traditional functional scientific programming is supported by a wide range of libraries and can be used for high performance code production, but at the same time it can be painful to master due to the vast documentation and the often long argument list of many of the APIs out there.

**Compact Suite** aims to bridge the gap between the established codebases and the modern object oriented coding style, while maintaining the efficiency, robustness and performance the first offers. 

The first library in the suite is [**CLA3P (Compact Linear Algebra Parallel Portable Package)**](cla3p.mod/README.md) a high performance linear algebra library that uses smart OOP design patterns and an intuitive API that allows the user to produce high quality code with minimum effort.

<p align="right">(<a href="#top">back to top</a>)</p>




# Build and Install

To build and install the suite, follow these simple steps.

## Prerequisites

In order to build **Compact Suite** you will need:
  * [CMake](https://cmake.org) 3.7.0 and above
  * [GNU C++ compiler](https://gcc.gnu.org) (linux)
  * [Microsoft Visual Studio](https://visualstudio.microsoft.com) (windows)
  * [Intel&reg; Math Kernel Library](https://www.intel.com/content/www/us/en/developer/tools/oneapi/onemkl.html) (linux & windows) You can download it [here](https://www.intel.com/content/www/us/en/developer/tools/oneapi/onemkl-download.html).

## Installation Guide

For the **Compact Suite** installation guide see [INSTALL.md](INSTALL.md).

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
<compact_suite_install>/license : licensing related documents
```

<p align="right">(<a href="#top">back to top</a>)</p>




# License

Licensed under the [Apache License, Version 2.0](https://www.apache.org/licenses/LICENSE-2.0). See [license](LICENSE) and [notice](NOTICE) for more information.

<p align="right">(<a href="#top">back to top</a>)</p>




# Contact

Connor Kaufman - connor.kaufman.gh@outlook.com  
Project Link: [https://github.com/connorkauf/CompactSuite](https://github.com/connorkauf/CompactSuite)  
Report an issue: [https://github.com/connorkauf/CompactSuite/issues](https://github.com/connorkauf/CompactSuite/issues) 

<p align="right">(<a href="#top">back to top</a>)</p>



