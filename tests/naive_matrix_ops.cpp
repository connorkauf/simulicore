// this file inc
#include "naive_matrix_ops.hpp"

// system

// 3rd

// cla3p
#include "cla3p/src/bulk/dns.hpp"

/*-------------------------------------------------*/
uint_t  ddabs1(uint_t     x) { return          x ; }
int_t   ddabs1(int_t      x) { return std::abs(x); }
real_t  ddabs1(real_t     x) { return std::abs(x); }
real4_t ddabs1(real4_t    x) { return std::abs(x); }
real_t  ddabs1(complex_t  x) { return std::abs(x); }
real4_t ddabs1(complex8_t x) { return std::abs(x); }
/*-------------------------------------------------*/
