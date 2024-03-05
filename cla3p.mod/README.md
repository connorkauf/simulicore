<a name="readme-top"></a>




# Overview




## Table of contents

1. [About CLA3P](#about-cla3p)
2. [How to use CLA3P](#how-to-use-cla3p)
3. [Useful info](#useful-info)
4. [Documentation](#documentation)
5. [Third-Party Dependencies](#third-party-dependencies)
6. [Examples](#examples)
7. [License](#license)
8. [Contact](#contact)




<a name="about-cla3p"></a>
## About CLA3P

**Compact Linear Algebra Parallel Portable Package** is a modern lightweight numerical linear algebra library distributed as a part of [**SimuliCore**](https://connorkauf.github.io/SimuliCore/index.html).  
With its minimalistic design **CLA3P** is ideal for beginners, while the advanced API offering allows experienced users get peak performance.

Starting with dense linear algebra support as a base framework, as well a sparse algebra addition, **CLA3P** will constantly evolve and expand to new fields such as sparse linear solvers, custom matrix decomposition implementations, eigenvalue problem solvers and many more.

### Features so far

**CLA3P** is a new and constantly evolving library. The currently supported and near-future features are:

- [x] Dense Matrix algebra
- [x] Sparse Matrix algebra
- [x] Smart operator sets with symbolic layer where applicable
- [x] Property specification for matrices
- [x] Column & Block operations
- [x] Vector/Matrix content referencing
- [x] Dense linear system solvers
- [ ] Dense QR decompositions
- [ ] Dense eigensolvers
- [ ] Sparse linear system solvers

All the above are supported by a wide range of **operators** for easy development, as well as an **advanced functional math interface** for peak performance. Choose which one fits your needs and start coding! The list will be expanded with new features on every new version. Feel free to [contact](https://connorkauf.github.io/SimuliCore/index.html#contact) us and submit your requests.

<p align="right">(<a href="#readme-top">back to top</a>)</p>




<a name="how-to-use-cla3p"></a>
## How to use CLA3P

**CLA3P** artifacts are located in your **SimuliCore** installation directory. You can use them simply by:
* including directory `<simulicore_install>/include`
* linking your code with the shared library located in `<simulicore_install>/lib`
* linking with 3rd party dependencies

**CLA3P** comes with 32bit and 64bit integer interfaces.  
* For using the 32bit integer interface, link with the **cla3p** library (libcla3p.so or cla3p.lib).  
* For using the 64bit integer interface you will need to:
  1. Add `-DCLA3P_I64` to your compilation flags
  2. Link with the **cla3p_i64** library (libcla3p_i64.so or cla3p_i64.lib).

```cmake
#
# sample linux CMake setup
#

include(<simulicore_install>/3rd/mkl.lin.cmake)
set(CLA3P_INC <simulicore_install>/include)
set(CLA3P_LIB -L<simulicore_install>/lib -lcla3p)

add_executable(<target> main.cpp)
target_include_directories(<target> PRIVATE ${CLA3P_INC})
target_link_libraries(<target> ${CLA3P_LIB} ${MKL_LIB})
```
See section [Third-Party Dependencies](#third-party-dependencies) for more information.

<p align="right">(<a href="#readme-top">back to top</a>)</p>




<a name="useful-info"></a>
## Useful info

In order to ensure a minimum-copy policy, copy constructors for the basic math objects are disabled for now. Objects can be explicitly copied using function calls. Move constructors are defined for rapid data passing between objects. This guarantees total control over memory and keeps allocations to a minimum.  

**CLA3P** comes with an intuitive operator-based interface, as well as an advanced functional-based interface for maximum efficiency. For example, a transpose matrix-vector multiplication operation can be called using operators
```cpp
Y = A.transpose() * X;
```
or by using the mult() function
```cpp
Y = cla3p::ops::mult(1., cla3p::op_t::T, A, X);
```
Thanks to the **CLA3P Virtuals** symbolic layer, `A.transpose()` is not calculated explicitly. Instead a virtually transposed matrix is generated and plugged in the multiplication operator. This way the above calculations are virtually the same with no extra memory allocated, or explicit calculations performed. **CLA3P Virtuals** are currently available for dense objects. Sparse virtual support will soon be supported.

<p align="right">(<a href="#readme-top">back to top</a>)</p>




<a name="documentation"></a>
## Documentation

You can find the latest **CLA3P** version documentation [here](https://connorkauf.github.io/SimuliCore/v1.0.0/cla3p/html/index.html).

<p align="right">(<a href="#readme-top">back to top</a>)</p>




<a name="third-party-dependencies"></a>
## Third-Party Dependencies

**CLA3P** depends on [**Intel&reg; Math Kernel Library**](https://www.intel.com/content/www/us/en/developer/tools/oneapi/onemkl.html) in order to accelerate calculations. See this [guide](https://github.com/connorkauf/SimuliCore/blob/stable-latest/3rd/mkl.md) about linking with **Intel&reg; MKL** library.

Also, in the examples folder `<simulicore_install>/examples/cla3p` you can find examples on how to compile your own project using **CLA3P** and **Intel&reg; MKL**.

<p align="right">(<a href="#readme-top">back to top</a>)</p>




<a name="examples"></a>
## Examples

Folder `<simulicore_install>/examples/cla3p` contains numerus examples describing the basics of **CLA3P**.  

### Building examples on linux
From a linux terminal:
```sh
cd <simulicore_install>/examples/cla3p
./example_builder.sh
```
All example executables are located in the `i32/bin` and `i64/bin` directories, for the respective integer interface.  
Select an example `ex<number>_<description>.sh` and run it:
```sh
./i32/bin/ex01a_dense_vector_create.sh
```

### Building examples on windows
Open directory `<simulicore_install>/examples/cla3p` in Visual Studio and compile.  
Set the CMake variable `-DCLA3P_EXAMPLES_I64=true` to build examples using the 64bit integer interface.  
All example executables are located in the `ixx/bin` directory. ixx is either i32 or i64 depending on the integer interface selected.  
Select an example `ex<number>_<description>.bat` and run it on Visual Studio terminal:
```sh
./i32/bin/ex01a_dense_vector_create.bat
```

<p align="right">(<a href="#readme-top">back to top</a>)</p>




<a name="license"></a>
## License

Distributed as a part of [**SimuliCore**](https://connorkauf.github.io/SimuliCore/index.html) licensed under the [Apache License, Version 2.0](https://www.apache.org/licenses/LICENSE-2.0).

<p align="right">(<a href="#readme-top">back to top</a>)</p>




<a name="contact"></a>
## Contact

**CLA3P** is spanking new, so feel free to contact us about anything regarding this software.  
Please share your opinions, future requests and documentation clarifications, or report an issue [here](https://connorkauf.github.io/SimuliCore/index.html#contact).

<p align="right">(<a href="#readme-top">back to top</a>)</p>


