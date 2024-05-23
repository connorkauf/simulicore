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

#ifndef CLA3P_LINSOL_HPP_
#define CLA3P_LINSOL_HPP_

#include "cla3p/linsol/lapack_base.hpp"
#include "cla3p/linsol/lapack_auto.hpp"
#include "cla3p/linsol/lapack_llt.hpp"
#include "cla3p/linsol/lapack_ldlt.hpp"
#include "cla3p/linsol/lapack_lu.hpp"
#include "cla3p/linsol/lapack_complete_lu.hpp"

#include "cla3p/linsol/pardiso_base.hpp"
#include "cla3p/linsol/pardiso_auto.hpp"
#include "cla3p/linsol/pardiso_llt.hpp"
#include "cla3p/linsol/pardiso_ldlt.hpp"
#include "cla3p/linsol/pardiso_lu.hpp"
#include "cla3p/linsol/pardiso_symmetric_lu.hpp"

#endif // CLA3P_LINSOL_HPP_
