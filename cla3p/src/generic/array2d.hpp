#ifndef CLA3P_ARRAY2D_HPP_
#define CLA3P_ARRAY2D_HPP_

#include <string>

#include "../types.hpp"

/*-------------------------------------------------*/
namespace cla3p { 
namespace dns {
/*-------------------------------------------------*/

/**
 * @nosubgrouping 
 * @brief A basic 2D array class.
 */
template <typename T_Scalar>
class Array2D {

	public:
		Array2D();
		~Array2D();

		/**
		 * @brief The row size.
		 * @return The number of rows in the 2D Array.
		 */
		uint_t rsize() const;

		/**
		 * @brief The column size.
		 * @return The number of columns in the 2D Array.
		 */
		uint_t csize() const;

		/**
		 * @brief The values array.
		 * @return The pointer to the numerical values of the object (column-major).
		 */
		T_Scalar* values();

		/**
		 * @copydoc values()
		 */
		const T_Scalar* values() const;

		/**
		 * @brief Test whether object is empty.
		 * @return whether the object is empty.
		 */
		bool empty() const;

		/**
		 * @brief Fills the object with a value.
		 *
		 * Sets all entries of the object to a single value.
		 *
		 * @param[in] val The value to be set.
		 */
		virtual void fill(T_Scalar val);

		/**
		 * @brief Prints the contents of the object.
		 * @param[in] nsd The number of significant digits (for real/complex types only, otherwise ignored).
		 */
		virtual void print(uint_t nsd = 3) const;

		/**
		 * @brief Prints the contents of the object to a string.
		 * @param[in] nsd The number of significant digits (for real/complex types only, otherwise ignored).
		 * @return The string containing the formatted numerical values of the object.
		 */
		virtual std::string toString(uint_t nsd = 3) const;

	protected:
		void alloc(uint_t, uint_t);
		void clear();
		void copyTo(Array2D<T_Scalar>&) const;
		void copyToShallow(Array2D<T_Scalar>&);

		virtual T_Scalar& operator()(uint_t i, uint_t j);
		virtual const T_Scalar& operator()(uint_t i, uint_t j) const;

#if 0
	protected:
		std::string info(bool is2D,
				const std::string&,
				const std::string&,
				const std::string&,
				const std::string&) const;

		Tr normOne() const;
		Tr normInf() const;
		Tr normMax() const;
		Tr normFro() const;
		Tr normEuc() const;

		T& operator()(uint_t i, uint_t j);
		const T& operator()(uint_t i, uint_t j) const;

		// not callcable from empty
		void transposeTo(GenericObject<T,Tr>&) const;
		void ctransposeTo(GenericObject<T,Tr>&) const;
		void conjugateIp();

		void convertToGeneral(GenericObject<T,Tr>&) const;
		void convertToGeneralIp();

		void gePermuteTo(GenericObject<T,Tr>&, const PermMatrix& P, const PermMatrix& Q) const;
		void gePermuteToLeft(GenericObject<T,Tr>&, const PermMatrix& P) const;
		void gePermuteToRight(GenericObject<T,Tr>&, const PermMatrix& Q) const;
		void xxPermuteToMirror(GenericObject<T,Tr>&, const PermMatrix& P) const;

		void gePermuteIp(const PermMatrix& P, const PermMatrix& Q);
		void gePermuteIpLeft(const PermMatrix& P);
		void gePermuteIpRight(const PermMatrix& Q);
		void xxPermuteIpMirror(const PermMatrix& P);

		void getBlock(GenericObject<T,Tr>&, uint_t ibgn, uint_t jbgn, uint_t ni, uint_t nj) const;
		void getBlockReference(GenericObject<T,Tr>&, uint_t ibgn, uint_t jbgn, uint_t ni, uint_t nj);
		void setBlock(const GenericObject<T,Tr>&, uint_t ibgn, uint_t jbgn);

		void getRealBlock(GenericObject<Tr,Tr>&, uint_t ibgn, uint_t jbgn, uint_t ni, uint_t nj) const;
		void getImagBlock(GenericObject<Tr,Tr>&, uint_t ibgn, uint_t jbgn, uint_t ni, uint_t nj) const;
		void setRealBlock(const GenericObject<Tr,Tr>&, uint_t ibgn, uint_t jbgn);
		void setImagBlock(const GenericObject<Tr,Tr>&, uint_t ibgn, uint_t jbgn);

		void getRealPart(GenericObject<Tr,Tr>&) const;
		void getImagPart(GenericObject<Tr,Tr>&) const;
		void setRealPart(const GenericObject<Tr,Tr>&);
		void setImagPart(const GenericObject<Tr,Tr>&);

		// creators
		void  blankCreator(const Property& pr, uint_t nr, uint_t nc, uint_t ldim);
		void   zeroCreator(const Property& pr, uint_t nr, uint_t nc, uint_t ldim);
		void randomCreator(const Property& pr, uint_t nr, uint_t nc, uint_t ldim);
		void   wrapCreator(const Property& pr, uint_t nr, uint_t nc, T *vals, uint_t ldv, bool bind);
#endif

	private:
		uint_t    m_rsize;
		uint_t    m_csize;
		T_Scalar* m_values;

		void setRsize(uint_t);
		void setCsize(uint_t);
		void setValues(T_Scalar*);

		void defaults();
};

/*-------------------------------------------------*/
} // namespace dns
} // namespace cla3p
/*-------------------------------------------------*/

#endif // CLA3P_ARRAY2D_HPP_
