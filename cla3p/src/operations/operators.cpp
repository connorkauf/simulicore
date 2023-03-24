// this file inc
#include "operators.hpp"

// system

// 3rd

// cla3p
#include "math_ops.hpp"
#include "../linsol/dns_auto_lsolver.hpp"

/*-------------------------------------------------*/
static const cla3p::Operation noOp = cla3p::Operation(cla3p::op_t::N);
/*-------------------------------------------------*/

void operator+=(cla3p::dns::RiVector& trg, const cla3p::dns::RiVector& src) { cla3p::ops::update(1, src, trg); }
void operator+=(cla3p::dns::RdVector& trg, const cla3p::dns::RdVector& src) { cla3p::ops::update(1, src, trg); }
void operator+=(cla3p::dns::RfVector& trg, const cla3p::dns::RfVector& src) { cla3p::ops::update(1, src, trg); }
void operator+=(cla3p::dns::CdVector& trg, const cla3p::dns::CdVector& src) { cla3p::ops::update(1, src, trg); }
void operator+=(cla3p::dns::CfVector& trg, const cla3p::dns::CfVector& src) { cla3p::ops::update(1, src, trg); }

void operator+=(cla3p::dns::RiMatrix& trg, const cla3p::dns::RiMatrix& src) { cla3p::ops::update(1, src, trg); }
void operator+=(cla3p::dns::RdMatrix& trg, const cla3p::dns::RdMatrix& src) { cla3p::ops::update(1, src, trg); }
void operator+=(cla3p::dns::RfMatrix& trg, const cla3p::dns::RfMatrix& src) { cla3p::ops::update(1, src, trg); }
void operator+=(cla3p::dns::CdMatrix& trg, const cla3p::dns::CdMatrix& src) { cla3p::ops::update(1, src, trg); }
void operator+=(cla3p::dns::CfMatrix& trg, const cla3p::dns::CfMatrix& src) { cla3p::ops::update(1, src, trg); }

/*-------------------------------------------------*/

void operator-=(cla3p::dns::RiVector& trg, const cla3p::dns::RiVector& src) { cla3p::ops::update(-1, src, trg); }
void operator-=(cla3p::dns::RdVector& trg, const cla3p::dns::RdVector& src) { cla3p::ops::update(-1, src, trg); }
void operator-=(cla3p::dns::RfVector& trg, const cla3p::dns::RfVector& src) { cla3p::ops::update(-1, src, trg); }
void operator-=(cla3p::dns::CdVector& trg, const cla3p::dns::CdVector& src) { cla3p::ops::update(-1, src, trg); }
void operator-=(cla3p::dns::CfVector& trg, const cla3p::dns::CfVector& src) { cla3p::ops::update(-1, src, trg); }

void operator-=(cla3p::dns::RiMatrix& trg, const cla3p::dns::RiMatrix& src) { cla3p::ops::update(-1, src, trg); }
void operator-=(cla3p::dns::RdMatrix& trg, const cla3p::dns::RdMatrix& src) { cla3p::ops::update(-1, src, trg); }
void operator-=(cla3p::dns::RfMatrix& trg, const cla3p::dns::RfMatrix& src) { cla3p::ops::update(-1, src, trg); }
void operator-=(cla3p::dns::CdMatrix& trg, const cla3p::dns::CdMatrix& src) { cla3p::ops::update(-1, src, trg); }
void operator-=(cla3p::dns::CfMatrix& trg, const cla3p::dns::CfMatrix& src) { cla3p::ops::update(-1, src, trg); }

/*-------------------------------------------------*/

cla3p::dns::RiVector operator+(const cla3p::dns::RiVector& srcA, const cla3p::dns::RiVector& srcB) { return cla3p::ops::add(1, srcA, 1, srcB); }
cla3p::dns::RdVector operator+(const cla3p::dns::RdVector& srcA, const cla3p::dns::RdVector& srcB) { return cla3p::ops::add(1, srcA, 1, srcB); }
cla3p::dns::RfVector operator+(const cla3p::dns::RfVector& srcA, const cla3p::dns::RfVector& srcB) { return cla3p::ops::add(1, srcA, 1, srcB); }
cla3p::dns::CdVector operator+(const cla3p::dns::CdVector& srcA, const cla3p::dns::CdVector& srcB) { return cla3p::ops::add(1, srcA, 1, srcB); }
cla3p::dns::CfVector operator+(const cla3p::dns::CfVector& srcA, const cla3p::dns::CfVector& srcB) { return cla3p::ops::add(1, srcA, 1, srcB); }

cla3p::dns::RiMatrix operator+(const cla3p::dns::RiMatrix& srcA, const cla3p::dns::RiMatrix& srcB) { return cla3p::ops::add(1, srcA, 1, srcB); }
cla3p::dns::RdMatrix operator+(const cla3p::dns::RdMatrix& srcA, const cla3p::dns::RdMatrix& srcB) { return cla3p::ops::add(1, srcA, 1, srcB); }
cla3p::dns::RfMatrix operator+(const cla3p::dns::RfMatrix& srcA, const cla3p::dns::RfMatrix& srcB) { return cla3p::ops::add(1, srcA, 1, srcB); }
cla3p::dns::CdMatrix operator+(const cla3p::dns::CdMatrix& srcA, const cla3p::dns::CdMatrix& srcB) { return cla3p::ops::add(1, srcA, 1, srcB); }
cla3p::dns::CfMatrix operator+(const cla3p::dns::CfMatrix& srcA, const cla3p::dns::CfMatrix& srcB) { return cla3p::ops::add(1, srcA, 1, srcB); }

/*-------------------------------------------------*/

cla3p::dns::RiVector operator-(const cla3p::dns::RiVector& srcA, const cla3p::dns::RiVector& srcB) { return cla3p::ops::add(1, srcA, -1, srcB); }
cla3p::dns::RdVector operator-(const cla3p::dns::RdVector& srcA, const cla3p::dns::RdVector& srcB) { return cla3p::ops::add(1, srcA, -1, srcB); }
cla3p::dns::RfVector operator-(const cla3p::dns::RfVector& srcA, const cla3p::dns::RfVector& srcB) { return cla3p::ops::add(1, srcA, -1, srcB); }
cla3p::dns::CdVector operator-(const cla3p::dns::CdVector& srcA, const cla3p::dns::CdVector& srcB) { return cla3p::ops::add(1, srcA, -1, srcB); }
cla3p::dns::CfVector operator-(const cla3p::dns::CfVector& srcA, const cla3p::dns::CfVector& srcB) { return cla3p::ops::add(1, srcA, -1, srcB); }

cla3p::dns::RiMatrix operator-(const cla3p::dns::RiMatrix& srcA, const cla3p::dns::RiMatrix& srcB) { return cla3p::ops::add(1, srcA, -1, srcB); }
cla3p::dns::RdMatrix operator-(const cla3p::dns::RdMatrix& srcA, const cla3p::dns::RdMatrix& srcB) { return cla3p::ops::add(1, srcA, -1, srcB); }
cla3p::dns::RfMatrix operator-(const cla3p::dns::RfMatrix& srcA, const cla3p::dns::RfMatrix& srcB) { return cla3p::ops::add(1, srcA, -1, srcB); }
cla3p::dns::CdMatrix operator-(const cla3p::dns::CdMatrix& srcA, const cla3p::dns::CdMatrix& srcB) { return cla3p::ops::add(1, srcA, -1, srcB); }
cla3p::dns::CfMatrix operator-(const cla3p::dns::CfMatrix& srcA, const cla3p::dns::CfMatrix& srcB) { return cla3p::ops::add(1, srcA, -1, srcB); }

/*-------------------------------------------------*/

cla3p::dns::RiVector operator*(const cla3p::dns::RiMatrix& srcA, const cla3p::dns::RiVector& srcX) { return cla3p::ops::mult(1, noOp, srcA, srcX); }
cla3p::dns::RdVector operator*(const cla3p::dns::RdMatrix& srcA, const cla3p::dns::RdVector& srcX) { return cla3p::ops::mult(1, noOp, srcA, srcX); }
cla3p::dns::RfVector operator*(const cla3p::dns::RfMatrix& srcA, const cla3p::dns::RfVector& srcX) { return cla3p::ops::mult(1, noOp, srcA, srcX); }
cla3p::dns::CdVector operator*(const cla3p::dns::CdMatrix& srcA, const cla3p::dns::CdVector& srcX) { return cla3p::ops::mult(1, noOp, srcA, srcX); }
cla3p::dns::CfVector operator*(const cla3p::dns::CfMatrix& srcA, const cla3p::dns::CfVector& srcX) { return cla3p::ops::mult(1, noOp, srcA, srcX); }

cla3p::dns::RiMatrix operator*(const cla3p::dns::RiMatrix& srcA, const cla3p::dns::RiMatrix& srcB) { return cla3p::ops::mult(1, noOp, srcA, noOp, srcB); }
cla3p::dns::RdMatrix operator*(const cla3p::dns::RdMatrix& srcA, const cla3p::dns::RdMatrix& srcB) { return cla3p::ops::mult(1, noOp, srcA, noOp, srcB); }
cla3p::dns::RfMatrix operator*(const cla3p::dns::RfMatrix& srcA, const cla3p::dns::RfMatrix& srcB) { return cla3p::ops::mult(1, noOp, srcA, noOp, srcB); }
cla3p::dns::CdMatrix operator*(const cla3p::dns::CdMatrix& srcA, const cla3p::dns::CdMatrix& srcB) { return cla3p::ops::mult(1, noOp, srcA, noOp, srcB); }
cla3p::dns::CfMatrix operator*(const cla3p::dns::CfMatrix& srcA, const cla3p::dns::CfMatrix& srcB) { return cla3p::ops::mult(1, noOp, srcA, noOp, srcB); }

/*-------------------------------------------------*/

cla3p::dns::RiVector operator*(const cla3p::PermMatrix& srcP, const cla3p::dns::RiVector& srcX){ return srcX.permute(srcP); }
cla3p::dns::RdVector operator*(const cla3p::PermMatrix& srcP, const cla3p::dns::RdVector& srcX){ return srcX.permute(srcP); }
cla3p::dns::RfVector operator*(const cla3p::PermMatrix& srcP, const cla3p::dns::RfVector& srcX){ return srcX.permute(srcP); }
cla3p::dns::CdVector operator*(const cla3p::PermMatrix& srcP, const cla3p::dns::CdVector& srcX){ return srcX.permute(srcP); }
cla3p::dns::CfVector operator*(const cla3p::PermMatrix& srcP, const cla3p::dns::CfVector& srcX){ return srcX.permute(srcP); }

cla3p::dns::RiMatrix operator*(const cla3p::PermMatrix& srcP, const cla3p::dns::RiMatrix& srcA){ return srcA.permuteLeft(srcP); }
cla3p::dns::RdMatrix operator*(const cla3p::PermMatrix& srcP, const cla3p::dns::RdMatrix& srcA){ return srcA.permuteLeft(srcP); }
cla3p::dns::RfMatrix operator*(const cla3p::PermMatrix& srcP, const cla3p::dns::RfMatrix& srcA){ return srcA.permuteLeft(srcP); }
cla3p::dns::CdMatrix operator*(const cla3p::PermMatrix& srcP, const cla3p::dns::CdMatrix& srcA){ return srcA.permuteLeft(srcP); }
cla3p::dns::CfMatrix operator*(const cla3p::PermMatrix& srcP, const cla3p::dns::CfMatrix& srcA){ return srcA.permuteLeft(srcP); }

cla3p::dns::RiMatrix operator*(const cla3p::dns::RiMatrix& srcA, const cla3p::PermMatrix& srcP){ return srcA.permuteRight(srcP); }
cla3p::dns::RdMatrix operator*(const cla3p::dns::RdMatrix& srcA, const cla3p::PermMatrix& srcP){ return srcA.permuteRight(srcP); }
cla3p::dns::RfMatrix operator*(const cla3p::dns::RfMatrix& srcA, const cla3p::PermMatrix& srcP){ return srcA.permuteRight(srcP); }
cla3p::dns::CdMatrix operator*(const cla3p::dns::CdMatrix& srcA, const cla3p::PermMatrix& srcP){ return srcA.permuteRight(srcP); }
cla3p::dns::CfMatrix operator*(const cla3p::dns::CfMatrix& srcA, const cla3p::PermMatrix& srcP){ return srcA.permuteRight(srcP); }

/*-------------------------------------------------*/

template <typename T>
static void default_linear_solution_ip(const T& A, T& X)
{
	cla3p::dns::LSolverAuto<T> solver;
	solver.decompose(A);
	solver.solve(X);
}

template <typename T>
static T default_linear_solution(const T& A, const T& X)
{
	T ret = X.copy();
	default_linear_solution_ip(A, ret);
	return ret.move();
}

template <typename T, typename Tvec>
static void default_linear_solution_vec_ip(const T& A, Tvec& X)
{
	T tmp = X.rmatrix();
	default_linear_solution_ip(A, tmp);
}

template <typename T, typename Tvec>
static Tvec default_linear_solution_vec(const T& A, const Tvec& X)
{
	Tvec ret = X.copy();
	default_linear_solution_vec_ip(A, ret);
	return ret.move();
}

cla3p::dns::RdVector operator/(const cla3p::dns::RdVector& srcX, const cla3p::dns::RdMatrix& srcA) { return default_linear_solution_vec(srcA, srcX); }
cla3p::dns::RfVector operator/(const cla3p::dns::RfVector& srcX, const cla3p::dns::RfMatrix& srcA) { return default_linear_solution_vec(srcA, srcX); }
cla3p::dns::CdVector operator/(const cla3p::dns::CdVector& srcX, const cla3p::dns::CdMatrix& srcA) { return default_linear_solution_vec(srcA, srcX); }
cla3p::dns::CfVector operator/(const cla3p::dns::CfVector& srcX, const cla3p::dns::CfMatrix& srcA) { return default_linear_solution_vec(srcA, srcX); }

cla3p::dns::RdMatrix operator/(const cla3p::dns::RdMatrix& srcX, const cla3p::dns::RdMatrix& srcA) { return default_linear_solution(srcA, srcX); }
cla3p::dns::RfMatrix operator/(const cla3p::dns::RfMatrix& srcX, const cla3p::dns::RfMatrix& srcA) { return default_linear_solution(srcA, srcX); }
cla3p::dns::CdMatrix operator/(const cla3p::dns::CdMatrix& srcX, const cla3p::dns::CdMatrix& srcA) { return default_linear_solution(srcA, srcX); }
cla3p::dns::CfMatrix operator/(const cla3p::dns::CfMatrix& srcX, const cla3p::dns::CfMatrix& srcA) { return default_linear_solution(srcA, srcX); }

void operator/=(cla3p::dns::RdVector& srcX, const cla3p::dns::RdMatrix& srcA) { default_linear_solution_vec_ip(srcA, srcX); }
void operator/=(cla3p::dns::RfVector& srcX, const cla3p::dns::RfMatrix& srcA) { default_linear_solution_vec_ip(srcA, srcX); }
void operator/=(cla3p::dns::CdVector& srcX, const cla3p::dns::CdMatrix& srcA) { default_linear_solution_vec_ip(srcA, srcX); }
void operator/=(cla3p::dns::CfVector& srcX, const cla3p::dns::CfMatrix& srcA) { default_linear_solution_vec_ip(srcA, srcX); }

void operator/=(cla3p::dns::RdMatrix& srcX, const cla3p::dns::RdMatrix& srcA) { default_linear_solution_ip(srcA, srcX); }
void operator/=(cla3p::dns::RfMatrix& srcX, const cla3p::dns::RfMatrix& srcA) { default_linear_solution_ip(srcA, srcX); }
void operator/=(cla3p::dns::CdMatrix& srcX, const cla3p::dns::CdMatrix& srcA) { default_linear_solution_ip(srcA, srcX); }
void operator/=(cla3p::dns::CfMatrix& srcX, const cla3p::dns::CfMatrix& srcA) { default_linear_solution_ip(srcA, srcX); }

/*-------------------------------------------------*/

