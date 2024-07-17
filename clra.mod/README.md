<a name="readme-top"></a>




# Overview




## Table of contents

1. [About CLRA](#about-clra)
2. [How to use CLRA](#how-to-use-clra)
3. [Documentation](#documentation)
4. [License](#license)
5. [Contact](#contact)




<a name="about-clra"></a>
## About CLRA

**Compact Low Rank Approximations** is a **CLA3P** plugin for low-rank matrix support. It follows the same design patterns as the
base **CLA3P** module and is distributed as a part of [**SimuliCore**](https://connorkauf.github.io/simulicore/index.html).
At the moment the **CLRA** library is available upon request. You can request a copy of the library via [email](https://connorkauf.github.io/simulicore/index.html#contact).

### Features so far

**CLRA** is an expansion to **CLA3P** and has all the low-rank complementary features:

- [ ] Low-Rank Matrix algebra
- [x] Dense matrix to Low-Rank matirx conversion (standard)
- [x] Dense matrix to Low-Rank matirx conversion (fast)
- [ ] Hybrid matrix (Dense/Low-Rank)
- [ ] Algebraic operator interface
- [ ] Block Low-Rank Matrix
- [ ] Block Low-Rank Linear Solver

<p align="right">(<a href="#readme-top">back to top</a>)</p>




<a name="how-to-use-clra"></a>
## How to use CLRA

**CLRA** as well as **CLA3P** artifacts are located in your **SimuliCore** installation directory. You can use them simply by:
* including directory `<simulicore_install>/include`
* linking your code with the shared libraries located in `<simulicore_install>/lib`
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
set(CLRA_INC <simulicore_install>/include)
set(CLRA_LIB -L<simulicore_install>/lib -clra -lcla3p)

add_executable(<target> main.cpp)
target_include_directories(<target> PRIVATE ${CLRA_INC})
target_link_libraries(<target> ${CLRA_LIB} ${MKL_LIB})
```

<p align="right">(<a href="#readme-top">back to top</a>)</p>




<a name="documentation"></a>
## Documentation

You can find the latest **CLRA** version documentation [here](https://connorkauf.github.io/simulicore/v1.3.0/clra/html/index.html).

<p align="right">(<a href="#readme-top">back to top</a>)</p>




<a name="license"></a>
## License

<!-- Distributed as a part of [**SimuliCore**](https://connorkauf.github.io/simulicore/index.html) licensed under
the [Apache License, Version 2.0](https://www.apache.org/licenses/LICENSE-2.0). -->
**CLRA** is closed source at the moment, license pending.

<p align="right">(<a href="#readme-top">back to top</a>)</p>




<a name="contact"></a>
## Contact

**CLRA** is spanking new, so feel free to contact us about anything regarding this software.  
Please share your opinions, future requests and documentation clarifications, or report an issue [here](https://connorkauf.github.io/simulicore/index.html#contact).

<p align="right">(<a href="#readme-top">back to top</a>)</p>
