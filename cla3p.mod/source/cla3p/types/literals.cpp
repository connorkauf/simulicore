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
#include "cla3p/types/literals.hpp"

// system

// 3rd

// cla3p

/*-------------------------------------------------*/
namespace cla3p {
namespace msg {
/*-------------------------------------------------*/
std::string Unknown()
{ 
	return "Unknown"; 
}
/*-------------------------------------------------*/
/*-------------------------------------------------*/
/*-------------------------------------------------*/
std::string Integer()
{ 
	return "Integer"; 
}
/*-------------------------------------------------*/
std::string UnsignedInteger()
{ 
	return "Unsigned " + Integer(); 
}
/*-------------------------------------------------*/
std::string Real()
{ 
	return "Real"; 
}
/*-------------------------------------------------*/
std::string Complex()
{ 
	return "Complex"; 
}
/*-------------------------------------------------*/
std::string Single()
{ 
	return "Single (32bit)"; 
}
/*-------------------------------------------------*/
std::string Double()
{ 
	return "Double (64bit)"; 
}
/*-------------------------------------------------*/
std::string Dense()
{ 
	return "Dense"; 
}
/*-------------------------------------------------*/
std::string SparseCsc()
{ 
	return "Sparse (csc)"; 
}
/*-------------------------------------------------*/
std::string SparseCoo()
{ 
	return "Sparse (coo)"; 
}
/*-------------------------------------------------*/
std::string Vector()
{ 
	return "Vector"; 
}
/*-------------------------------------------------*/
std::string Matrix()
{ 
	return "Matrix"; 
}
/*-------------------------------------------------*/
std::string PermutationMatrix()
{ 
	return "Permutation " + Matrix(); 
}
/*-------------------------------------------------*/
std::string DenseVector()
{ 
	return Dense() + " " + Vector(); 
}
/*-------------------------------------------------*/
std::string DenseMatrix ()
{ 
	return Dense() + " " + Matrix(); 
}
/*-------------------------------------------------*/
std::string SparseCscMatrix()
{
	return SparseCsc() + " " + Matrix(); 
}
/*-------------------------------------------------*/
std::string SparseCooMatrix()
{
	return SparseCoo() + " " + Matrix(); 
}
/*-------------------------------------------------*/
/*-------------------------------------------------*/
/*-------------------------------------------------*/
std::string NoOperation()
{ 
	return "No operation";
}
/*-------------------------------------------------*/
std::string TransposeOperation()
{ 
	return "Transpose";
}
/*-------------------------------------------------*/
std::string ConjugateTransposeOperation()
{ 
	return "Conjugate Transpose";
}
/*-------------------------------------------------*/
/*-------------------------------------------------*/
/*-------------------------------------------------*/
std::string General()
{ 
	return "General"; 
}
/*-------------------------------------------------*/
std::string Symmetric()
{ 
	return "Symmetric"; 
}
/*-------------------------------------------------*/
std::string Hermitian()
{ 
	return "Hermitian"; 
}
/*-------------------------------------------------*/
std::string Triangular()
{ 
	return "Triangular/Trapezoidal"; 
}
/*-------------------------------------------------*/
std::string Skew()
{ 
	return "Skew"; 
}
/*-------------------------------------------------*/
/*-------------------------------------------------*/
/*-------------------------------------------------*/
std::string Full()
{ 
	return "Full"; 
}
/*-------------------------------------------------*/
std::string Upper()
{ 
	return "Upper"; 
}
/*-------------------------------------------------*/
std::string Lower()
{ 
	return "Lower"; 
}
/*-------------------------------------------------*/
std::string Left()
{
	return "Left";
}
/*-------------------------------------------------*/
std::string Right()
{
	return "Right";
}
/*-------------------------------------------------*/
std::string DecompAuto()
{
	return "Auto detection decomposition method";
}
/*-------------------------------------------------*/
std::string DecompLLt()
{
	return "Definite Cholesky (LL')";
}
/*-------------------------------------------------*/
std::string DecompLDLt()
{
	return "Indefinite Cholesky (LDL')";
}
/*-------------------------------------------------*/
std::string DecompPartialLU()
{
	return "Partial Pivoting LU";
}
/*-------------------------------------------------*/
std::string DecompCompleteLU()
{
	return "Complete Pivoting LU";
}
/*-------------------------------------------------*/
std::string DecompSymmetricLU()
{
	return "Structurally Symmetric LU";
}
/*-------------------------------------------------*/
} // namespace msg
} // namespace cla3p
/*-------------------------------------------------*/
