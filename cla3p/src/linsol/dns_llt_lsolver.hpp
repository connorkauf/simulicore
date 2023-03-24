#ifndef CLA3P_DNS_LLT_LSOLVER_HPP_
#define CLA3P_DNS_LLT_LSOLVER_HPP_

/**
 * @file
 * Custom dense linear solvers
 */

#include "dns_default_lsolver.hpp"

/*-------------------------------------------------*/
namespace cla3p { 
namespace dns { 
/*-------------------------------------------------*/

/**
 * @ingroup dense_linear_solvers_group
 * @nosubgrouping
 * @brief The definite Cholesky (LL') linear solver for dense matrices.
 */
template <typename T>
class SpdCholesky : public DefaultLSolver<T> {

	public:

		// no copy
		SpdCholesky(const SpdCholesky&) = delete;
		SpdCholesky& operator=(const SpdCholesky&) = delete;

		/**
		 * @brief The default constructor.
		 *
		 * Constructs an empty solver object.
		 */
		SpdCholesky();

		/**
		 * @brief The dimensional constructor.
		 *
		 * Constructs a preallocated solver object with n^2 buffered size.
		 */
		SpdCholesky(uint_t n);

		/**
		 * @brief Destroys the solver.
		 */
		~SpdCholesky();

		/**
		 * @brief Performs matrix decomposition.
		 * @param[in] mat The matrix to be decomposed.
		 */
		void decompose(const T& mat) override;

		/**
		 * @brief Performs in-place matrix decomposition.
		 * @param[in] mat The matrix to be decomposed, destroyed after the operation.
		 */
		void idecompose(T& mat) override;

		/**
		 * @brief Performs in-place matrix solution.
		 * @param[in] rhs The right hand side matrix, overwritten with the solution.
		 */
		void solve(T& rhs) const override;

	private:
		void fdecompose();
};

/*-------------------------------------------------*/
} // namespace dns
} // namespace cla3p
/*-------------------------------------------------*/

#endif // CLA3P_DNS_LLT_LSOLVER_HPP_
