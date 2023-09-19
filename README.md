The location of this file is marked as <compact-suite-root>


Prepare to install
------------------
CMake version 3.7.0 and above is needed.
Intel MKL configuration is needed. Edit file
<compact-suite-root>/3rd/mkl.lin.cmake (linux os)
<compact-suite-root>/3rd/mkl.win.cmake (windows os)
and set the path(s) to your Intel MKL installation directories.
Do not change the variable names.
For MacOS Intel MKL is not supported.


Build & Install
---------------
Choose a build directory: <build-dir>
For 32bit integer version of cla3p run: cmake -S <compact-suite-root> -B <build-dir>
For 64bit integer version of cla3p run: cmake -S <compact-suite-root> -B <build-dir> -DCLA3P_USE_I64=true
cd <build-dir>
make
make install


Installation contents
---------------------
The default installation path is <compact-suite-root>/install

install/include   : the compact suite include directory
install/lib       : the compact suite library directory
install/examples  : the compact suite examples (for documentation purposes)
install/doc       : the compact suite documentation (doxygen needed)
install/bin       : a sample executable for developing purposes

