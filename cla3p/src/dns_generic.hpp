#ifndef CLA3P_DNS_GENERIC_HPP_
#define CLA3P_DNS_GENERIC_HPP_

#include <iostream>

#include "types.hpp"

/*-------------------------------------------------*/
namespace cla3p {
namespace dns {
/*-------------------------------------------------*/
template <class T>
class GenericObject {

	public:
		GenericObject();
		~GenericObject();
		GenericObject(const GenericObject<T>&) = delete;
		GenericObject<T>& operator=(const GenericObject<T>&) = delete;
		GenericObject(GenericObject<T>&&);
		GenericObject<T>& operator=(GenericObject<T>&&);

		bool isready() const;
		void clear();
		void unbind();

		GenericObject<T> copy() const;
		GenericObject<T> clone();
		GenericObject<T> move();

		void info(
				const std::string& msg,
				const std::string& otype,
				const std::string& dtype,
				const std::string& dprec) const;
		void print(uint_t nsd = 3) const;

		T& operator()(uint_t i, uint_t j);
		const T& operator()(uint_t i, uint_t j) const;

		// static members
		static GenericObject<T> init(const Property& prop, uint_t nrows, uint_t ncols, uint_t ld);
		static GenericObject<T> zero(const Property& prop, uint_t nrows, uint_t ncols, uint_t ld);
		static GenericObject<T> random(const Property& prop, uint_t nrows, uint_t ncols, uint_t ld);
		static GenericObject<T> map(const Property& prop, uint_t nrows, uint_t ncols, T *values, uint_t ld);

	protected:
		void set_nrows (uint_t           nrows );
		void set_ncols (uint_t           ncols );
		void set_ld    (uint_t           ld    );
		void set_values(T*               values);
		void set_prop  (const Property&  prop  );
		void set_owner (bool             owner );

		uint_t          nrows () const;
		uint_t          ncols () const;
		uint_t          ld    () const;
		T*              values()      ;
		const T*        values() const;
		const Property& prop  () const;
		bool            owner () const;

	private:
		uint_t   m_nrows ;
		uint_t   m_ncols ;
		uint_t   m_ld    ;
		T*       m_values;
		Property m_prop  ;
		bool     m_owner ;

		GenericObject(uint_t nrows, uint_t ncols, T *values, uint_t ld, const Property& prop, bool owner);
		void defaults();
};

/*-------------------------------------------------*/
} // namespace dns
} // namespace cla3p
/*-------------------------------------------------*/

#endif // CLA3P_DNS_GENERIC_HPP_
