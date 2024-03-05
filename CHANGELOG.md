# [v1.1.0] - 2024-03-05

SimuliCore next version with various features, bug-fixes and patches.

## CLA3P Module

### New Features
- Vector dot product
- Add sparse matrix utility class (coordinate format)
- Add sparse matrix class (compressed sparse column format)
- [CLA3P-25](https://github.com/connorkauf/SimuliCore/issues/25) Virtual Operations Implementation.
- [CLA3P-34](https://github.com/connorkauf/SimuliCore/issues/34) Implementation of sparse algebra

### Changes
- Rename dns::XxObject member function "scale()" to "iscale()"
- Move PxMatrix to 'prm' namespace: prm::PxMatrix

### Fixes

# [v1.0.0] - 2023-12-13

SimuliCore first release.

## CLA3P Module

### New Features
- Dense Linear Algebra
  - Vectors
  - Matrices
  - Single/Double Precision
  - Real/Complex Arithmetic
- Algebraic Operations
  - Addition/Subtraction
  - Matrix-Vector multiplications
  - Matrix-Matrix multiplications
- Block Operations
- Data Referencing
- Permutations
- Standard Dense Linear Solvers
- Operators Set

