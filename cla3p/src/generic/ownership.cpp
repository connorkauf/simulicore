// this file inc
#include "ownership.hpp"

// system

// 3rd

// cla3p

/*-------------------------------------------------*/
namespace cla3p {
/*-------------------------------------------------*/
Ownership::Ownership()
{
	defaults();
}
/*-------------------------------------------------*/
Ownership::~Ownership()
{
}
/*-------------------------------------------------*/
bool Ownership::owner() const 
{
	return m_owner; 
}
/*-------------------------------------------------*/
void Ownership::setOwner(bool owner) 
{ 
	m_owner = owner; 
}
/*-------------------------------------------------*/
void Ownership::clear()
{
	defaults();
}
/*-------------------------------------------------*/
void Ownership::defaults()
{
	setOwner(false);
}
/*-------------------------------------------------*/
void Ownership::unbind()
{
	setOwner(false);
}
/*-------------------------------------------------*/
} // namespace cla3p
/*-------------------------------------------------*/
