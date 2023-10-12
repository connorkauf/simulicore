<a name="readme-top"></a>


## About CLA3P

**Compact Linear Algebra Parallel Portable Package** is a modern lightweignt numerical linear algebra library distributed as a part of [**Compact Suite**](https://github.com/connorkauf/CompactSuite). With its minimalistic design **CLA3P** is ideal for beginners, while the advanced API offering allows experienced users get peak performance.

Starting with dense linear algebra support as a base framework, **CLA3P** will constantly evolve and expand to new fields such as sparse linear algebra, custom matrix decomposition implementations, eigenvalue problem solvers and many more.

<p align="right">(<a href="#readme-top">back to top</a>)</p>




## How to use CLA3P

You can use **CLA3P** from your **Compact Suite** installation directory simply by:
* linking your code with the shared library located in `<compact_suite_install>/lib`
* including directory `<compact_suite_install>/include`

**CLA3P** comes with a 32bit and 64bit integer interface.  
For the 32bit integer interface, link with the **cla3p** library.  
For the 64bit integer interface, add the definition `CLA3P_I64` to your compilation configuration and link with the **cla3p_i64** library.  

<p align="right">(<a href="#readme-top">back to top</a>)</p>




