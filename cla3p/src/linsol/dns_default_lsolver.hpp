#ifndef CLA3P_DNS_DEFAULT_LSOLVER_HPP_
#define CLA3P_DNS_DEFAULT_LSOLVER_HPP_

/**
 * @file
 * Default class for dense linear solvers
 */

#include <vector>

#include "../types.hpp"

/*-------------------------------------------------*/
namespace cla3p { 
namespace dns { 
/*-------------------------------------------------*/

/**
 * @ingroup dense_linear_solvers_group
 * @nosubgrouping
 * @brief The default linear solver for dense matrices.
 */
template <typename T>
class DefaultLSolver {

	public:

		// no copy
		DefaultLSolver(const DefaultLSolver&) = delete;
		DefaultLSolver& operator=(const DefaultLSolver&) = delete;

		/**
		 * @brief The default constructor.
		 *
		 * Constructs an empty solver object.
		 */
		DefaultLSolver();

		/**
		 * @brief Destroys the solver.
		 */
		~DefaultLSolver();

		/**
		 * @brief Clears the solver.
		 */
		virtual void clear();

		/**
		 * @brief Performs matrix decomposition.
		 * @param[in] mat The matrix to be decomposed.
		 */
		virtual void decompose(const T& mat);

		/**
		 * @brief Performs in-place matrix decomposition.
		 * @param[in] mat The matrix to be decomposed, destroyed after the operation.
		 */
		virtual void idecompose(T& mat);

		/**
		 * @brief Performs in-place matrix solution.
		 * @param[in] rhs The right hand side matrix, overwritten with the solution.
		 */
		virtual void solve(T& rhs) const;

	protected:
		int_t info() const;
		T& factor();
		const T& factor() const;
		std::vector<int_t>& ipiv1();
		const std::vector<int_t>& ipiv1() const;

	private:
		int_t m_info;
		bool m_decomp_success;
		T m_factor;
		std::vector<int_t> m_ipiv1;

		void defaults();
		void clear_privately();
		void reset_info();
		void reset_decomp_flg();
		void update_decomp_flg();
		void check_decomp_info() const;
		void check_decomp_input(const T&) const;
		void check_solve_input(const T&) const;
		void absorbInput(const T&);
		void fdecompose();
};

/*-------------------------------------------------*/
} // namespace dns
} // namespace cla3p
/*-------------------------------------------------*/

#endif // CLA3P_DNS_DEFAULT_LSOLVER_HPP_
