<a name="readme-top"></a>


## About CLA3P

**Compact Linear Algebra Parallel Portable Package** is a modern lightweignt numerical linear algebra library distributed as a part of [**Compact Suite**](https://github.com/connorkauf/CompactSuite). With its minimalistic design **CLA3P** is ideal for beginners, while the advanced API offering allows experienced users get peak performance.

Starting with dense linear algebra support as a base framework, **CLA3P** will constantly evolve and expand to new fields such as sparse linear algebra, custom matrix decomposition implementations, eigenvalue problem solvers and many more.

<p align="right">(<a href="#readme-top">back to top</a>)</p>




## How to use CLA3P

**CLA3P** artifacts are located in your **Compact Suite** installation directory. You can use them simply by:
* including directory `<compact_suite_install>/include`
* linking your code with the shared library located in `<compact_suite_install>/lib`
* linking with 3rd party dependencies

**CLA3P** comes with a 32bit or 64bit integer interface.  
* For using the 32bit integer interface, link with the **cla3p** library (libcla3p.so or cla3p.lib).  
* For using the 64bit integer interface you will need to:
  1. Add `-DCLA3P_I64` to your compilation flags
  2. Link with the **cla3p_i64** library (libcla3p_i64.so or cla3p_i64.lib).

```
#
# sample linux CMake setup
#

include("<compact_suite_install>/3rd/mkl.lin.cmake")
set(CLA3P_INC "<compact_suite_install>/include")
set(CLA3P_LIB -L<compact_suite_install>/lib -lcla3p)

add_executable(<target> main.cpp)
target_include_directories(<target> PUBLIC ${CLA3P_INC})
target_link_libraries(<target> ${CLA3P_LIB} ${MKL_LIB})
```
See section [Linking](#linking) for more information.

<p align="right">(<a href="#readme-top">back to top</a>)</p>




## Useful info

In order to ensure a minimum-copy policy, copy constructors for the basic math objects are disabled for now. Objects can be explicitly copied using function calls. Move constructors are defined for rapid data passing between objects. This guarantees total control over memory and keeps allocations to a minimum.  

**CLA3P** comes with an intuitive operator-based interface, as well as an advanced functional-based interface for maximum efficiency. For example, a transpose matrix-vector multiplication operation can be called using operators
```
Y = A.transpose() * X;
```
or by skipping the explicit transposition of A and using the mult() function
```
Y = cla3p::ops::mult(1., cla3p::op_t::T, A, X);
```
The user has the convinience of quickly writing an early implementation of a code chunk, verify that it works and then gradually improve performance by identifying and treating such cases.

<p align="right">(<a href="#readme-top">back to top</a>)</p>




## Documentation

A quick reference guide will be available shortly.

<p align="right">(<a href="#readme-top">back to top</a>)</p>




<a name="linking"></a>
## Linking

**CLA3P** depends on [**Intel Math Kernel Library**](https://www.intel.com/content/www/us/en/developer/tools/oneapi/onemkl.html) in order to accelerate calculations. Check files located in `<compact_suite_install>/3rd` for a guide about linking with **Intel MKL** library. Also, in the examples folder `<compact_suite_install>/examples/cla3p` you can also find examples on how to compile your own project using **CLA3P** and **Intel MKL**.

<p align="right">(<a href="#readme-top">back to top</a>)</p>




## Examples

Folder `<compact_suite_install>/examples/cla3p` contains numerus examples describing the basics of **CLA3P**.  

### Building examples on linux
From a linux terminal:
```
cd <compact_suite_install>/examples/cla3p
./example_builder.sh
```
All example executables are located in the `bin` directory.  
Select an example `ex<number & descritpion>.sh` and run it:
```
./bin/ex01a_dense_vector_create.sh
```

### Building examples on windows
Open directory `<compact_suite_install>/examples/cla3p` in Visual Studio and compile.  
Do not forget to set the CMake option `-DCLA3P_USE_I64` if needed.  
All example executables are located in the `bin` directory.  
Select an example `ex<number & descritpion>.bat` and run it on Visual Studio terminal:
```
./bin/ex01a_dense_vector_create.bat
```


<p align="right">(<a href="#readme-top">back to top</a>)</p>




## Contact

**CLA3P** is spanking new, so feel free to contact us about anything regarding this software. Please share your opinions, future requests and issue reporting using the links below: 

Connor Kaufman - connor.kaufman.gh@outlook.com  
Report an issue: [https://github.com/connorkauf/CompactSuite/issues](https://github.com/connorkauf/CompactSuite/issues) 

<p align="right">(<a href="#readme-top">back to top</a>)</p>


