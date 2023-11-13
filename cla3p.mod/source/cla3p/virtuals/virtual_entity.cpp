/*
 * Copyright 2023-2024 Connor C. Kaufman (connor.kaufman.gh@outlook.com)
 * 
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 *     http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

// this file inc
#include "cla3p/virtuals/virtual_entity.hpp"

// system

// 3rd

// cla3p
#include "cla3p/dense.hpp"
#include "cla3p/virtuals/virtual_object.hpp"
#include "cla3p/virtuals/virtual_pair.hpp"

/*-------------------------------------------------*/
namespace cla3p {
/*-------------------------------------------------*/
template <typename T_Object, typename T_Virtual>
T_Virtual VirtualEntity<T_Object,T_Virtual>::scale(T_Scalar val) const
{
	T_Virtual ret = self();
	ret.iscale(val);
	return ret;
}
/*-------------------------------------------------*/
template <typename T_Object, typename T_Virtual>
T_Virtual VirtualEntity<T_Object,T_Virtual>::conjugate() const
{
	T_Virtual ret = self();
	ret.iconjugate();
	return ret;
}
/*-------------------------------------------------*/
/*-------------------------------------------------*/
/*-------------------------------------------------*/
template class VirtualEntity<dns::RdVector, VirtualVector<dns::RdVector>>;
template class VirtualEntity<dns::RfVector, VirtualVector<dns::RfVector>>;
template class VirtualEntity<dns::CdVector, VirtualVector<dns::CdVector>>;
template class VirtualEntity<dns::CfVector, VirtualVector<dns::CfVector>>;
/*-------------------------------------------------*/
template class VirtualEntity<dns::RdMatrix, VirtualMatrix<dns::RdMatrix>>;
template class VirtualEntity<dns::RfMatrix, VirtualMatrix<dns::RfMatrix>>;
template class VirtualEntity<dns::CdMatrix, VirtualMatrix<dns::CdMatrix>>;
template class VirtualEntity<dns::CfMatrix, VirtualMatrix<dns::CfMatrix>>;
/*-------------------------------------------------*/
template class VirtualEntity<dns::RdVector, VirtualPairMv<dns::RdVector>>;
template class VirtualEntity<dns::RfVector, VirtualPairMv<dns::RfVector>>;
template class VirtualEntity<dns::CdVector, VirtualPairMv<dns::CdVector>>;
template class VirtualEntity<dns::CfVector, VirtualPairMv<dns::CfVector>>;
/*-------------------------------------------------*/
template class VirtualEntity<dns::RdMatrix, VirtualPairMm<dns::RdMatrix>>;
template class VirtualEntity<dns::RfMatrix, VirtualPairMm<dns::RfMatrix>>;
template class VirtualEntity<dns::CdMatrix, VirtualPairMm<dns::CdMatrix>>;
template class VirtualEntity<dns::CfMatrix, VirtualPairMm<dns::CfMatrix>>;
/*-------------------------------------------------*/
} // namespace cla3p
/*-------------------------------------------------*/
