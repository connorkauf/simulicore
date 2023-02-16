#ifndef CLA3P_GENERIC_DNS_HPP_
#define CLA3P_GENERIC_DNS_HPP_

/** @file
 * Generic dense object definitions.
 */

#include <string>

#include "../types.hpp"
#include "universal.hpp"

/*-------------------------------------------------*/
namespace cla3p { 
class PermMatrix;
namespace dns {
/*-------------------------------------------------*/

/**
 * @brief The basic dense object generic class.
 *
 * All dense objects inherit from this class.
 */
template <typename T, typename Tr>
class GenericObject : public UniversalMetaData {

	public:

		// 
		// inherited args
		//

		/**
		 * @brief The values array.
		 * @return The pointer to the numerical values of the object (column-major).
		 */
		T* values();

		/**
		 * @brief The values array.
		 * @return The pointer to the numerical values of the object (column-major).
		 */
		const T* values() const;

		// 
		// inherited methods - callable from empty
		//

		/**
		 * @brief Clears the object.
		 *
		 * Deallocates owned data and resets all members.
		 */
		void clear();

		/**
		 * @brief Prints the contents of the object.
		 * @param[in] nsd The number of significant digits (for real/complex types only, otherwise ignored).
		 */
		void print(uint_t nsd = 3) const;

		/**
		 * @brief Prints the contents of the object to a string.
		 * @param[in] nsd The number of significant digits (for real/complex types only, otherwise ignored).
		 * @return The string containing the formatted numerical values of the object.
		 */
		std::string printToString(uint_t nsd = 3) const;

	protected:
		GenericObject();
		GenericObject(prop_t ptype, uint_t nr, uint_t nc, uint_t ldim, bool wipe);
		~GenericObject();

		// no copy
		GenericObject(const GenericObject<T,Tr>&) = delete;
		GenericObject<T,Tr>& operator=(const GenericObject<T,Tr>&) = delete;

		// move
		GenericObject(GenericObject<T,Tr>&&);
		GenericObject<T,Tr>& operator=(GenericObject<T,Tr>&&);

		// args
		void setLd    (uint_t          ldim  );
		void setValues(T*              values);
		void setProp  (const Property& prop  );

		uint_t          ld  () const;
		const Property& prop() const;

		// callable from empty
		void scaleWith(T coeff);
		void copyTo(GenericObject<T,Tr>&) const;
		void moveTo(GenericObject<T,Tr>&);
		void cloneTo(GenericObject<T,Tr>&);

		std::string info(bool is2D,
				const std::string&,
				const std::string&,
				const std::string&,
				const std::string&) const;

		Tr normOne() const;
		Tr normInf() const;
		Tr normMax() const;
		Tr normFro() const;

		T& operator()(uint_t i, uint_t j);
		const T& operator()(uint_t i, uint_t j) const;

		// not callcable from empty
		void transposeTo(GenericObject<T,Tr>&) const;
		void ctransposeTo(GenericObject<T,Tr>&) const;

		void gePermuteTo(GenericObject<T,Tr>&, const PermMatrix& P, const PermMatrix& Q) const;
		void gePermuteToLeft(GenericObject<T,Tr>&, const PermMatrix& P) const;
		void gePermuteToRight(GenericObject<T,Tr>&, const PermMatrix& Q) const;
		void shPermuteTo(GenericObject<T,Tr>&, const PermMatrix& P) const;

		void gePermuteIp(const PermMatrix& P, const PermMatrix& Q);
		void gePermuteIpLeft(const PermMatrix& P);
		void gePermuteIpRight(const PermMatrix& Q);
		void shPermuteIp(const PermMatrix& P);

		void getBlock(GenericObject<T,Tr>&, uint_t ibgn, uint_t jbgn, uint_t ni, uint_t nj) const;
		void getBlockReference(GenericObject<T,Tr>&, uint_t ibgn, uint_t jbgn, uint_t ni, uint_t nj);
		void setBlock(const GenericObject<T,Tr>&, uint_t ibgn, uint_t jbgn);

		// creators
		void  blankCreator(prop_t ptype, uint_t nr, uint_t nc, uint_t ldim);
		void   zeroCreator(prop_t ptype, uint_t nr, uint_t nc, uint_t ldim);
		void randomCreator(prop_t ptype, uint_t nr, uint_t nc, uint_t ldim);
		void   wrapCreator(prop_t ptype, uint_t nr, uint_t nc, T *vals, uint_t ldv, bool bind);

	private:
		uint_t   m_ld    ;
		T*       m_values;
		Property m_prop  ;

		void defaults();
		void creator(prop_t ptype, uint_t nr, uint_t nc, T *vals, uint_t ldv, bool owner);
};
/*-------------------------------------------------*/
} // namespace dns
} // namespace cla3p
/*-------------------------------------------------*/

#endif // CLA3P_GENERIC_DNS_HPP_
