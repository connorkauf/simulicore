/*
 * Copyright 2023-2024 Connor C. Kaufman (connor.kaufman.gh@outlook.com)
 * 
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 *     http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

// this file inc
#include "cla3p/linsol/pardiso_base.hpp"

// system
#include <sstream>
#include <algorithm>

// 3rd

// cla3p
#include "cla3p/dense.hpp"
#include "cla3p/sparse.hpp"
#include "cla3p/support/utils.hpp"
#include "cla3p/proxies/mkl_pardiso_proxy.hpp"
#include "cla3p/error/exceptions.hpp"
#include "cla3p/error/literals.hpp"
#include "cla3p/checks/basic_checks.hpp"
#include "cla3p/checks/decomp_xx_checks.hpp"
#include "cla3p/checks/solve_checks.hpp"

/*-------------------------------------------------*/
namespace cla3p {
/*-------------------------------------------------*/
template <typename T_Matrix>
PardisoBase<T_Matrix>::PardisoBase(decomp_t decompType)
	: m_decompType(decompType)
{
	defaults();
}
/*-------------------------------------------------*/
template <typename T_Matrix>
PardisoBase<T_Matrix>::~PardisoBase()
{
	clear();
}
/*-------------------------------------------------*/
template <typename T_Matrix>
decomp_t PardisoBase<T_Matrix>::decompType() const
{
	return m_decompType;
}
/*-------------------------------------------------*/
template <typename T_Matrix>
std::string PardisoBase<T_Matrix>::name() const
{
	std::ostringstream ss;
	ss << "Pardiso " << decompType();
	return ss.str();
}
/*-------------------------------------------------*/
template <typename T_Matrix>
void PardisoBase<T_Matrix>::defaults()
{
	std::fill(m_pt, m_pt + PT_DIM, 0);
	std::fill(m_iparm, m_iparm + IPARM_DIM, 0);

	pardiso::ImmutableParams<T_Scalar>::setToIparm(m_iparm);

	m_mtype = mtype_t::Undefined;
	m_maxfct = 1;
	m_msglvl = 0;

	m_dim = 0;
	m_colptr = nullptr;
	m_rowidx = nullptr;
	m_values = nullptr;
}
/*-------------------------------------------------*/
template <typename T_Matrix>
void PardisoBase<T_Matrix>::clear()
{
	pardiso::GlobalParams::clear();
	pardiso::AnalysisParams::clear();
	pardiso::DecompParams::clear();
	pardiso::SolveParams::clear();

	m_permBuffer.clear();
	m_permMatrix.clear();

	callDriver(phase_t::ClearAll);

	defaults();
}
/*-------------------------------------------------*/
template <typename T_Matrix>
void PardisoBase<T_Matrix>::clearNumeric()
{
	callDriver(phase_t::ClearNumeric);
}
/*-------------------------------------------------*/
template <typename T_Matrix>
void PardisoBase<T_Matrix>::updateIparmAnalysis()
{
	pardiso::GlobalParams::setToIparm(m_iparm);
	pardiso::AnalysisParams::setToIparm(m_iparm);

	if(m_iparm[10] == pardiso::Undefined()) {

		if(m_mtype == mtype_t::RealNonSymmetric || m_mtype == mtype_t::ComplexNonSymmetric) 
			m_iparm[10] = 1;
		else
			m_iparm[10] = 0;

	} // iparm10

	if(m_iparm[12] == pardiso::Undefined()) {

		if(m_mtype == mtype_t::RealNonSymmetric || m_mtype == mtype_t::ComplexNonSymmetric) 
			m_iparm[12] = 1;
		else
			m_iparm[12] = 0;

	} // iparm12
}
/*-------------------------------------------------*/
template <typename T_Matrix>
void PardisoBase<T_Matrix>::prepareForAnalysis(const T_Matrix& mat)
{
	decomp_generic_check(mat);

	clearReservedParams();
	clearOutputParams();

	m_mtype = deduceMtype(mat);

	if(m_mtype == mtype_t::Undefined) {
		throw err::Exception(msg::PardisoError() + ": Matrix (" + mat.prop().name() + ") is incompatible with " + name());
	} // error

	updateIparmAnalysis();
	updateMatrixInfo(mat);
	configureFillReducer();
}
/*-------------------------------------------------*/
template <typename T_Matrix>
void PardisoBase<T_Matrix>::analysis(const T_Matrix& mat)
{
	prepareForAnalysis(mat);
	callDriver(phase_t::Analysis);
}
/*-------------------------------------------------*/
template <typename T_Matrix>
void PardisoBase<T_Matrix>::updateIparmDecomposition()
{
	pardiso::GlobalParams::setToIparm(m_iparm);
	pardiso::DecompParams::setToIparm(m_iparm);

	if(m_iparm[9] == pardiso::Undefined()) {

		if(m_mtype == mtype_t::RealNonSymmetric || m_mtype == mtype_t::ComplexNonSymmetric)
			m_iparm[9] = 13;
		else if(m_mtype == mtype_t::RealSymmetricIndef || m_mtype == mtype_t::ComplexHermitianIndef || m_mtype == mtype_t::ComplexSymmetric)
			m_iparm[9] = 8;
		else
			m_iparm[9] = 0;

	} // iparm09
}
/*-------------------------------------------------*/
template <typename T_Matrix>
void PardisoBase<T_Matrix>::prepareForDecomposition(const T_Matrix& mat)
{
	decomp_generic_check(mat);

	if(m_mtype == mtype_t::Undefined) {
		throw err::Exception(msg::PardisoError() + ": Analysis not performed");
	} // error

	if(m_mtype != deduceMtype(mat)) {
		throw err::Exception(msg::PardisoError() + ": Matrix (" + mat.prop().name() + ") is incompatible with analysis phase");
	} // error

	updateMatrixInfo(mat);
	updateIparmDecomposition();
}
/*-------------------------------------------------*/
template <typename T_Matrix>
void PardisoBase<T_Matrix>::decompose(const T_Matrix& mat)
{
	prepareForDecomposition(mat);
	callDriver(phase_t::Numeric);
}
/*-------------------------------------------------*/
template <typename T_Matrix>
void PardisoBase<T_Matrix>::updateIparmSolve()
{
	pardiso::GlobalParams::setToIparm(m_iparm);
	pardiso::SolveParams::setToIparm(m_iparm);

	if(m_mtype == mtype_t::RealNonSymmetric || m_mtype == mtype_t::RealStructurallySymmetric)
		m_iparm[11] = 2;
	else if( m_mtype == mtype_t::ComplexNonSymmetric || m_mtype == mtype_t::ComplexStructurallySymmetric)
		m_iparm[11] = 2;
	else
		m_iparm[11] = 0;
}
/*-------------------------------------------------*/
template <typename T_Matrix>
void PardisoBase<T_Matrix>::prepareForSolution(const T_DnsMatrix& rhs, T_DnsMatrix& sol)
{
	similarity_check(
    rhs.prop(), rhs.nrows(), rhs.ncols(),
    sol.prop(), sol.nrows(), sol.ncols());

	default_solve_input_check(m_dim, rhs);
	default_solve_input_check(m_dim, sol);

	updateIparmSolve();
}
/*-------------------------------------------------*/
template <typename T_Matrix>
static void applyConjugationIfNeeded(bool conjop, const T_Matrix& A)
{
	if(conjop) {
		const_cast<T_Matrix&>(A).iconjugate();
	}
}
/*-------------------------------------------------*/
template <typename T_Matrix>
void PardisoBase<T_Matrix>::solve(const T_DnsMatrix& rhs, T_DnsMatrix& sol)
{
	if(!sol)
		sol = T_DnsMatrix::init(rhs.nrows(), rhs.ncols());

	if(rhs.nrows() == rhs.ld() && sol.nrows() == sol.ld()) {

		bool conjop = (m_mtype == mtype_t::ComplexHermitianPosdef || m_mtype == mtype_t::ComplexHermitianIndef);
		applyConjugationIfNeeded(conjop, rhs);

		try {
			prepareForSolution(rhs, sol);
			callDriver(phase_t::Solve, rhs.ncols(), const_cast<T_Scalar*>(rhs.values()), sol.values());
		} catch (...) {
			applyConjugationIfNeeded(conjop, rhs);
			throw;
		}

		applyConjugationIfNeeded(conjop, rhs);
		applyConjugationIfNeeded(conjop, sol);

	} else {

		for(uint_t j = 0; j < rhs.ncols(); j++) {
			Guard<T_Vector> grdBj = rhs.rcolumn(j);
			T_Vector Xj = sol.rcolumn(j);
			solve(grdBj.get(), Xj);
		} // j

	} // ld checks
}
/*-------------------------------------------------*/
template <typename T_Matrix>
void PardisoBase<T_Matrix>::solve(const T_Vector& rhs, T_Vector& sol)
{
	if(!sol)
		sol = T_Vector::init(rhs.size());

	Guard<T_DnsMatrix> grdRhs = rhs.rmatrix();
	T_DnsMatrix tmpSol = sol.rmatrix();
	solve(grdRhs.get(), tmpSol);
}
/*-------------------------------------------------*/
/*-------------------------------------------------*/
/*-------------------------------------------------*/
template <typename T_Matrix>
void PardisoBase<T_Matrix>::setVerbose(bool flg)
{
	m_msglvl = (flg ? 1 : 0);
}
/*-------------------------------------------------*/
template <typename T_Matrix>
typename PardisoBase<T_Matrix>::mtype_t 
PardisoBase<T_Matrix>::deduceMtype(const T_Matrix& mat)
{
	mtype_t ret = mtype_t::Undefined;

	decomp_t dtype = determineDecompType(decompType(), mat.prop());

	if(TypeTraits<T_Matrix>::is_real()) {

		if(mat.prop().isSymmetric() && mat.prop().isLower() && dtype == decomp_t::LLT        ) return mtype_t::RealSymmetricPosdef;
		if(mat.prop().isSymmetric() && mat.prop().isLower() && dtype == decomp_t::LDLT       ) return mtype_t::RealSymmetricIndef;
		if(mat.prop().isGeneral()                           && dtype == decomp_t::LU         ) return mtype_t::RealNonSymmetric;
		if(mat.prop().isGeneral()                           && dtype == decomp_t::SymmetricLU) return mtype_t::RealStructurallySymmetric;

	} else if(TypeTraits<T_Matrix>::is_complex()) {

		if(mat.prop().isHermitian() && mat.prop().isLower() && dtype == decomp_t::LLT        ) return mtype_t::ComplexHermitianPosdef;
		if(mat.prop().isHermitian() && mat.prop().isLower() && dtype == decomp_t::LDLT       ) return mtype_t::ComplexHermitianIndef;
		if(mat.prop().isSymmetric() && mat.prop().isLower() && dtype == decomp_t::LDLT       ) return mtype_t::ComplexSymmetric;
		if(mat.prop().isGeneral()                           && dtype == decomp_t::LU         ) return mtype_t::ComplexNonSymmetric;
		if(mat.prop().isGeneral()                           && dtype == decomp_t::SymmetricLU) return mtype_t::ComplexStructurallySymmetric;

	} // real/complex

	return ret;
}
/*-------------------------------------------------*/
template <typename T_Matrix>
void PardisoBase<T_Matrix>::updateMatrixInfo(const T_Matrix& mat)
{
	m_dim = mat.ncols();
	m_colptr = mat.colptr();
	m_rowidx = mat.rowidx();
	m_values = mat.values();
}
/*-------------------------------------------------*/
template <typename T_Matrix>
void PardisoBase<T_Matrix>::resizePerm(uint_t size)
{
	if(size > m_permBuffer.size()) {
		m_permBuffer.clear();
		m_permBuffer = prm::PiMatrix::init(size);
	}
	m_permMatrix = prm::PiMatrix::wrap(size, m_permBuffer.values(), false);
}
/*-------------------------------------------------*/
template <typename T_Matrix>
void PardisoBase<T_Matrix>::configureFillReducer()
{
	resizePerm(m_dim);

	if(userDefinedPermutation()) {

		if(m_dim != userPermMatrix().size())
			throw err::NoConsistency("User defined permutation matrix dimension mismatch");

		m_permMatrix = userPermMatrix();

	} // user defined perm
}
/*-------------------------------------------------*/
template <typename T_Matrix>
void PardisoBase<T_Matrix>::clearReservedParams()
{
	m_iparm[ 2] = 0;
	m_iparm[25] = 0;
	m_iparm[28] = 0;
	m_iparm[31] = 0;
	m_iparm[32] = 0;
	m_iparm[37] = 0;
	m_iparm[39] = 0;
	m_iparm[40] = 0;
	m_iparm[41] = 0;
	m_iparm[43] = 0;
	m_iparm[44] = 0;
	m_iparm[45] = 0;
	m_iparm[46] = 0;
	m_iparm[47] = 0;
	m_iparm[48] = 0;
	m_iparm[49] = 0;
	m_iparm[50] = 0;
	m_iparm[51] = 0;
	m_iparm[52] = 0;
	m_iparm[53] = 0;
	m_iparm[54] = 0;
	m_iparm[56] = 0;
	m_iparm[57] = 0;
	m_iparm[58] = 0;
	m_iparm[60] = 0;
	m_iparm[61] = 0;
	m_iparm[63] = 0;
}
/*-------------------------------------------------*/
template <typename T_Matrix>
void PardisoBase<T_Matrix>::clearOutputParams()
{
	m_iparm[ 6] = 0; // (output) Number of iterative refinement steps performed
	m_iparm[13] = 0; // (output) Number of perturbed pivots
	m_iparm[14] = 0; // (output) Peak memory on symbolic factorization
	m_iparm[15] = 0; // (output) Permanent memory on symbolic factorization
	m_iparm[16] = 0; // (output) Size of factors/Peak memory on numerical factorization and solution
	m_iparm[19] = 0; // (output) Report CG/CGS diagnostics
	m_iparm[21] = 0; // (output) Inertia: number of positive eigenvalues
	m_iparm[22] = 0; // (output) Inertia: number of negative eigenvalues
	m_iparm[29] = 0; // (output) Number of zero or negative pivots
	m_iparm[62] = 0; // (output) Size of the minimum OOC memory for numerical factorization and solution
}
/*-------------------------------------------------*/
template <typename T_Matrix>
void PardisoBase<T_Matrix>::callDriver(phase_t phase, int_t nrhs, T_Scalar *b, T_Scalar *x)
{
	int_t error = mkl::pardisoDriver(
    m_pt,
    m_maxfct,
    1,
    static_cast<int_t>(m_mtype),
    static_cast<int_t>(phase),
    static_cast<int_t>(m_dim),
    m_values,
    m_colptr,
    m_rowidx,
    m_permMatrix.values(),
    nrhs,
    m_iparm,
    m_msglvl,
    b,
    x);

	checkError(error);
}
/*-------------------------------------------------*/
template <typename T_Matrix>
void PardisoBase<T_Matrix>::checkError(int_t error) const
{
	if(error != 0)
		throw err::Exception(msg::PardisoError() + ": " + mkl::pardisoGetErrorMsg(error));
}
/*-------------------------------------------------*/
/*-------------------------------------------------*/
/*-------------------------------------------------*/
template <typename T_Matrix>
const prm::PiMatrix& PardisoBase<T_Matrix>::fillReducingOrdering() const
{
	return m_permMatrix;
}
/*-------------------------------------------------*/
template <typename T_Matrix>
int_t PardisoBase<T_Matrix>::iterativeRefinementSteps() const
{
	return m_iparm[6];
}
/*-------------------------------------------------*/
template <typename T_Matrix>
int_t PardisoBase<T_Matrix>::perturbedPivots() const
{
	return m_iparm[13];
}
/*-------------------------------------------------*/
template <typename T_Matrix>
int_t PardisoBase<T_Matrix>::peakAnalysisMemory() const
{
	return m_iparm[14];
}
/*-------------------------------------------------*/
template <typename T_Matrix>
int_t PardisoBase<T_Matrix>::permanentAnalysisMemory() const
{
	return m_iparm[15];
}
/*-------------------------------------------------*/
template <typename T_Matrix>
int_t PardisoBase<T_Matrix>::factorMemory() const
{
	return m_iparm[16];
}
/*-------------------------------------------------*/
template <typename T_Matrix>
int_t PardisoBase<T_Matrix>::inertiaPositive() const
{
	return m_iparm[21];
}
/*-------------------------------------------------*/
template <typename T_Matrix>
int_t PardisoBase<T_Matrix>::inertiaNegative() const
{
	return m_iparm[22];
}
/*-------------------------------------------------*/
template class PardisoBase<csc::RdMatrix>;
template class PardisoBase<csc::RfMatrix>;
template class PardisoBase<csc::CdMatrix>;
template class PardisoBase<csc::CfMatrix>;
/*-------------------------------------------------*/
} // namespace cla3p
/*-------------------------------------------------*/
