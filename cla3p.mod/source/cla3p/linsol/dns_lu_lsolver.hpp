#ifndef CLA3P_DNS_LU_LSOLVER_HPP_
#define CLA3P_DNS_LU_LSOLVER_HPP_

/**
 * @file
 * LU dense linear solver
 */

#include "cla3p/linsol/dns_lsolver_base.hpp"

/*-------------------------------------------------*/
namespace cla3p { 
namespace dns { 
/*-------------------------------------------------*/

/**
 * @ingroup module_index_linsol_dense
 * @nosubgrouping
 * @brief The partial pivoting LU linear solver for dense matrices.
 */
template <typename T_Matrix>
class LSolverLU : public LSolverBase<T_Matrix> {

	using T_Vector = typename BasicTypeTraits<T_Matrix>::vector_type;

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
		 * Constructs a preallocated solver object with n<sup>2</sup> buffered size.
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

#endif // CLA3P_DNS_LU_LSOLVER_HPP_
