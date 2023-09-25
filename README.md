<a name="readme-top"></a>




<details>
  <summary>Table of Contents</summary>
  <ol>
    <li>
      <a href="#about-the-project">About Compact Suite</a>
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

**Compact Suite** is a collection of C++ libraries that aims to modernize the scientific computation development.

Traditional functional scientific programming is supported by a wide range of libraries and can produce high performance code, but at the same time it can be painful to master due to the vast documentation and the often long argument list of many of the APIs out there.

Compact suite aims to bridge the gap between the established codebases and the modern object oriented way of coding, while maintaining the efficiency, robustness and performance the first offers. 

The first library in the suite is **Compact Linear Algebra Parallel Portable Package (CLA3P)** a high performing linear algebra library that uses smart OOP design patterns and an intuitive API that allows the user to produce high quality code with minimum effort.

<p align="right">(<a href="#readme-top">back to top</a>)</p>




## Getting Started

To get a local copy up, build and install the suite, follow these simple example steps.

### Prerequisites

In order to build Compact Suite you will need:
* CMake 3.7.0 and above
* Intel MKL
* A GNU C++ compiler (linux)
* Microsoft Visual Studio (windows)

### Linux Installation

1. Clone the repo
   ```sh
   git clone git@github.com:connorkauf/CompactSuite.git
   ```
   For the purposes of this file, the root directory is marked as `compact_suite_root`

2. Open and edit file
   ```sh
   <compact_suite_root>/3rd/mkl.lin.cmake
   ```
   and set paths `MKL_ROOT` and `ICC_ROOT` to point to your installed copy of Intel MKL and Intel Compiler respectively.

3. Choose a build directory `build-dir` and use cmake command to configure the project
   ```sh
   cmake -S <compact_suite_root> -B <build-dir>
   ```
   For extra configuration options see further below.

4. Go to `build-dir`
   ```sh
   cd <build-dir>
   ```
5. Compile and install 
   ```sh
   make
   make install
   ```

### Windows Installation

1. Clone the repo (using Git Bash)
   ```sh
   git clone git@github.com:connorkauf/CompactSuite.git
   ```
   For the purposes of this file, the root directory is marked as `compact_suite_root`

2. Open and edit file
   ```sh
   <compact_suite_root>/3rd/mkl.win.cmake
   ```
   and set paths `MKL_ROOT` and `ICC_ROOT` to point to your installed copy of Intel MKL and Intel Compiler respectively.

3. Start Microsoft Visual Studio and open the `compact_suite_root` directory.

4. Configure CMake from inside Microsoft Visual Studio (Project > CMake Settings for Compact Suite).

5. Compile (Build > Build All)

6. Install (Build > Install Compact Suite)

### Extra configuration arguments

You can define the variable `CLA3P_USE_I64` to make CLA3P use 64-bit integers.  
For Linux append `-DCLA3P_USE_I64=true` in the cmake command (step 3).  
For Windows add `-DCLA3P_USE_I64=true` in the section "CMake command arguments" in CMake Settings (step 4).

### Installation contents

The default installation path is 
* `compact_suite_root`/install for Linux
* `compact_suite_root`/out/install/`build-type` for Windows
```
install/include   : the compact suite include directory
install/lib       : the compact suite library directory
install/examples  : the compact suite examples (for documentation purposes)
install/doc       : the compact suite documentation (doxygen needed)
```

<p align="right">(<a href="#readme-top">back to top</a>)</p>




## License

Distributed under the MIT License. See `LICENSE.txt` for more information.

<p align="right">(<a href="#readme-top">back to top</a>)</p>




## Contact

Connor Kaufman - connor.kaufman.gh@outlook.com

Project Link: [https://github.com/connorkauf/CompactSuite](https://github.com/connorkauf/CompactSuite)

<p align="right">(<a href="#readme-top">back to top</a>)</p>



