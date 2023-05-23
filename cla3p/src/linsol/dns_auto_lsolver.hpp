#ifndef CLA3P_DNS_AUTO_LSOLVER_HPP_
#define CLA3P_DNS_AUTO_LSOLVER_HPP_

/**
 * @file
 * Auto detect method class for dense linear solvers
 */

#include "dns_lsolver_base.hpp"

/*-------------------------------------------------*/
namespace cla3p { 
namespace dns { 
/*-------------------------------------------------*/

/**
 * @ingroup dense_linear_solvers
 * @nosubgrouping
 * @brief The linear solver for dense matrices with auto method detection.
 */
template <typename T>
class LSolverAuto : public LSolverBase<T> {

	public:

		// no copy
		LSolverAuto(const LSolverAuto&) = delete;
		LSolverAuto& operator=(const LSolverAuto&) = delete;

		/**
		 * @brief The default constructor.
		 *
		 * Constructs an empty solver object.
		 */
		LSolverAuto();

		/**
		 * @brief The dimensional constructor.
		 *
		 * Constructs a preallocated solver object with n^2 buffered size.
		 */
		LSolverAuto(uint_t n);

		/**
		 * @brief Destroys the solver.
		 */
		~LSolverAuto();

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

#endif // CLA3P_DNS_AUTO_LSOLVER_HPP_
