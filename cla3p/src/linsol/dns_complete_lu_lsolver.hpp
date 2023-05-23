#ifndef CLA3P_DNS_COMPLETE_LU_LSOLVER_HPP_
#define CLA3P_DNS_COMPLETE_LU_LSOLVER_HPP_

/**
 * @file
 * LU dense linear solver with complete pivoting
 */

#include "dns_lsolver_base.hpp"

/*-------------------------------------------------*/
namespace cla3p { 
namespace dns { 
/*-------------------------------------------------*/

/**
 * @ingroup dense_linear_solvers
 * @nosubgrouping
 * @brief The complete pivoting LU linear solver for dense matrices.
 */
template <typename T>
class LSolverCompleteLU : public LSolverBase<T> {

	public:

		// no copy
		LSolverCompleteLU(const LSolverCompleteLU&) = delete;
		LSolverCompleteLU& operator=(const LSolverCompleteLU&) = delete;

		/**
		 * @brief The default constructor.
		 *
		 * Constructs an empty solver object.
		 */
		LSolverCompleteLU();

		/**
		 * @brief The dimensional constructor.
		 *
		 * Constructs a preallocated solver object with n^2 buffered size.
		 */
		LSolverCompleteLU(uint_t n);

		/**
		 * @brief Destroys the solver.
		 */
		~LSolverCompleteLU();

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

#endif // CLA3P_DNS_COMPLETE_LU_LSOLVER_HPP_
