#ifndef CLA3P_DNS_LDLT_LSOLVER_HPP_
#define CLA3P_DNS_LDLT_LSOLVER_HPP_

/**
 * @file
 * LDLt dense linear solver
 */

#include "dns_lsolver_base.hpp"

/*-------------------------------------------------*/
namespace cla3p { 
namespace dns { 
/*-------------------------------------------------*/

/**
 * @ingroup dense_linear_solvers
 * @nosubgrouping
 * @brief The indefinite Cholesky (LDL') linear solver for dense matrices.
 */
template <typename T_Matrix>
class LSolverLDLt : public LSolverBase<T_Matrix> {

	using T_Vector = typename BasicTypeTraits<T_Matrix>::vector_type;

	public:

		// no copy
		LSolverLDLt(const LSolverLDLt&) = delete;
		LSolverLDLt& operator=(const LSolverLDLt&) = delete;

		/**
		 * @brief The default constructor.
		 *
		 * Constructs an empty solver object.
		 */
		LSolverLDLt();

		/**
		 * @brief The dimensional constructor.
		 *
		 * Constructs a preallocated solver object with n^2 buffered size.
		 */
		LSolverLDLt(uint_t n);

		/**
		 * @brief Destroys the solver.
		 */
		~LSolverLDLt();

		/**
		 * @copydoc cla3p::dns::LSolverBase::reserve(uint_t n)
		 */
		void reserve(uint_t n) override;

		/**
		 * @copydoc cla3p::dns::LSolverBase::decompose()
		 */
		void decompose(const T_Matrix& mat) override;

		/**
		 * @copydoc cla3p::dns::LSolverBase::idecompose()
		 */
		void idecompose(T_Matrix& mat) override;

		/**
		 * @copydoc cla3p::dns::LSolverBase::solve(T_Matrix& rhs) const
		 */
		void solve(T_Matrix& rhs) const override;

		/**
		 * @copydoc cla3p::dns::LSolverBase::solve(T_Vector& rhs) const
		 */
		void solve(T_Vector& rhs) const override;

	private:
		void fdecompose();
};

/*-------------------------------------------------*/
} // namespace dns
} // namespace cla3p
/*-------------------------------------------------*/

#endif // CLA3P_DNS_LDLT_LSOLVER_HPP_
