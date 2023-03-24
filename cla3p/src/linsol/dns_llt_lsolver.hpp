#ifndef CLA3P_DNS_LLT_LSOLVER_HPP_
#define CLA3P_DNS_LLT_LSOLVER_HPP_

/**
 * @file
 * Custom dense linear solvers
 */

#include "dns_lsolver_base.hpp"

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
class LSolverLLt : public LSolverBase<T> {

	public:

		// no copy
		LSolverLLt(const LSolverLLt&) = delete;
		LSolverLLt& operator=(const LSolverLLt&) = delete;

		/**
		 * @brief The default constructor.
		 *
		 * Constructs an empty solver object.
		 */
		LSolverLLt();

		/**
		 * @brief The dimensional constructor.
		 *
		 * Constructs a preallocated solver object with n^2 buffered size.
		 */
		LSolverLLt(uint_t n);

		/**
		 * @brief Destroys the solver.
		 */
		~LSolverLLt();

		/**
		 * @copydoc cla3p::dns::LSolverBase::reserve(uint_t n)
		 */
		void reserve(uint_t n) override;

		/**
		 * @copydoc cla3p::dns::LSolverBase::decompose()
		 */
		void decompose(const T& mat) override;

		/**
		 * @copydoc cla3p::dns::LSolverBase::idecompose()
		 */
		void idecompose(T& mat) override;

		/**
		 * @copydoc cla3p::dns::LSolverBase::solve()
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
