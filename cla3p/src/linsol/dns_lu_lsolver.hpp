#ifndef CLA3P_DNS_LU_LSOLVER_HPP_
#define CLA3P_DNS_LU_LSOLVER_HPP_

/**
 * @file
 * LU dense linear solver
 */

#include "dns_lsolver_base.hpp"

/*-------------------------------------------------*/
namespace cla3p { 
namespace dns { 
/*-------------------------------------------------*/

/**
 * @ingroup dense_linear_solvers_group
 * @nosubgrouping
 * @brief The LU linear solver for dense matrices.
 */
template <typename T>
class LSolverLU : public LSolverBase<T> {

	public:

		// no copy
		LSolverLU(const LSolverLU&) = delete;
		LSolverLU& operator=(const LSolverLU&) = delete;

		/**
		 * @brief The default constructor.
		 *
		 * Constructs an empty solver object.
		 */
		LSolverLU();

		/**
		 * @brief The dimensional constructor.
		 *
		 * Constructs a preallocated solver object with n^2 buffered size.
		 */
		LSolverLU(uint_t n);

		/**
		 * @brief Destroys the solver.
		 */
		~LSolverLU();

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

#endif // CLA3P_DNS_LU_LSOLVER_HPP_
