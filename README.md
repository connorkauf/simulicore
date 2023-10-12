<a name="readme-top"></a>




<details>
  <summary>Table of Contents</summary>
  <ol>
    <li>
      <a href="#about-compact-suite">About Compact Suite</a>
    </li>
    <li>
      <a href="#getting-started">Getting Started</a>
      <ul>
        <li><a href="#prerequisites">Prerequisites</a></li>
        <li><a href="#linux-installation">Linux installation</a></li>
        <li><a href="#windows-installation">Windows installation</a></li>
        <li><a href="#extra-configuration-arguments">Extra configuration arguments</a></li>
        <li><a href="#installation-contents">Installation contents</a></li>
      </ul>
    </li>
    <li><a href="#license">License</a></li>
    <li><a href="#contact">Contact</a></li>
  </ol>
</details>




## About Compact Suite

**Compact Suite** is a collection of C++ libraries for scientific and computational development.

Traditional functional scientific programming is supported by a wide range of libraries and can be used for high performance code production, but at the same time it can be painful to master due to the vast documentation and the often long argument list of many of the APIs out there.

**Compact Suite** aims to bridge the gap between the established codebases and the modern object oriented coding style, while maintaining the efficiency, robustness and performance the first offers. 

The first library in the suite is [**CLA3P (Compact Linear Algebra Parallel Portable Package)**](cla3p.mod/README.md) a high performance linear algebra library that uses smart OOP design patterns and an intuitive API that allows the user to produce high quality code with minimum effort.

<p align="right">(<a href="#readme-top">back to top</a>)</p>




## Getting Started

To build and install the suite, follow these simple example steps.

### Prerequisites

In order to build **Compact Suite** you will need:
* [CMake](https://cmake.org) 3.7.0 and above
* [GNU C++ compiler](https://gcc.gnu.org) (linux)
* [Microsoft Visual Studio](https://visualstudio.microsoft.com) (windows)
* [Intel Math Kernel Library](https://www.intel.com/content/www/us/en/developer/tools/oneapi/onemkl.html) (linux & windows) You can download it [here](https://www.intel.com/content/www/us/en/developer/tools/oneapi/onemkl-download.html).
 
### Linux Installation

1. Open the terminal
  
2. Clone the repo
   ```sh
   git clone git@github.com:connorkauf/CompactSuite.git
   cd CompactSuite
   ```
   For the purposes of this document, the top directory is marked as `compact_suite_root`

3. Open file
   ```sh
   <compact_suite_root>/3rd/mkl.lin.cmake
   ```
   and set paths `MKL_ROOT` and `ICC_ROOT` to point to your installed copy of **Intel MKL** and **Intel Compiler** respectively.

   <a name="linux-step4"></a>
4. Choose a build directory `build_dir` and use cmake command to configure the project
   ```sh
   cmake -S <compact_suite_root> -B <build_dir>
   ```
   For extra configuration options see section [Extra configuration arguments](#extra-configuration-arguments) further below.

6. Go to `build_dir`
   ```sh
   cd <build_dir>
   ```
7. Compile and install 
   ```sh
   make
   make install
   ```

### Windows Installation

1. Clone the repo using a cloning method of your choice
   ```sh
   https: https://github.com/connorkauf/CompactSuite.git
   ssh: git@github.com:connorkauf/CompactSuite.git
   ```
   For the purposes of this document, the top directory is marked as `compact_suite_root`

2. Open file
   ```sh
   <compact_suite_root>/3rd/mkl.win.cmake
   ```
   and set paths `MKL_ROOT` and `ICC_ROOT` to point to your installed copy of **Intel MKL** and **Intel Compiler** respectively.

3. Start Microsoft Visual Studio and open the `compact_suite_root` directory.

   <a name="windows-step4"></a>
4. Configure CMake from inside Microsoft Visual Studio (Project > CMake Settings for Compact Suite).  
   For extra configuration options see section [Extra configuration arguments](#extra-configuration-arguments) further below.

6. Compile (Build > Build All)

7. Install (Build > Install Compact Suite)

### Extra configuration arguments

You can define the CMake variable `CLA3P_USE_I64` to make CLA3P use 64-bit integers.  
For Linux append `-DCLA3P_USE_I64=true` in the cmake command ([step 4](#linux-step4)).  
For Windows add `-DCLA3P_USE_I64=true` in the section "CMake command arguments" in CMake Settings ([step 4](#windows-step4)).

### Installation contents

The default installation path is 
* `compact_suite_root`/install for Linux
* `compact_suite_root`/out/install/`build-type` for Windows
```
<compact_suite_install>/include : the compact suite include directory
<compact_suite_install>/lib     : the compact suite library directory
<compact_suite_install>/3rd     : directory containing the 3rd party library configurations
<compact_suite_install>/examples: the compact suite examples directory
```

<p align="right">(<a href="#readme-top">back to top</a>)</p>




## License

Distributed under the MIT License. See `LICENSE.txt` for more information.

<p align="right">(<a href="#readme-top">back to top</a>)</p>




## Contact

Connor Kaufman - connor.kaufman.gh@outlook.com  
Project Link: [https://github.com/connorkauf/CompactSuite](https://github.com/connorkauf/CompactSuite)  
Report an issue: [https://github.com/connorkauf/CompactSuite/issues](https://github.com/connorkauf/CompactSuite/issues) 

<p align="right">(<a href="#readme-top">back to top</a>)</p>



