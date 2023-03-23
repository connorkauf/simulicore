#ifndef CLA3P_DNS_CUSTOM_LSOLVERS_HPP_
#define CLA3P_DNS_CUSTOM_LSOLVERS_HPP_

/**
 * @file
 * Custom dense linear solvers
 */

//#include "../types.hpp"
//#include "../dense.hpp"
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
		 * @copydoc cla3p::dns::DefaultLSolver::DefaultLSolver()
		 */
		SpdCholesky();

		/**
		 * @copydoc cla3p::dns::DefaultLSolver::DefaultLSolver(uint_t n)
		 */
		SpdCholesky(uint_t n);

		/**
		 * @copydoc cla3p::dns::DefaultLSolver::~DefaultLSolver()
		 */
		~SpdCholesky();

		/**
		 * @copydoc cla3p::dns::DefaultLSolver::decompose()
		 */
		void decompose(const T& mat) override;

		/**
		 * @copydoc cla3p::dns::DefaultLSolver::idecompose()
		 */
		void idecompose(T& mat) override;

		/**
		 * @copydoc cla3p::dns::DefaultLSolver::solve()
		 */
		void solve(T& rhs) const override;

	private:
		void fdecompose();
};

/*-------------------------------------------------*/
} // namespace dns
} // namespace cla3p
/*-------------------------------------------------*/

#endif // CLA3P_DNS_CUSTOM_LSOLVERS_HPP_
