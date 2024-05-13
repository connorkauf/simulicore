# [v1.2.1] - 2024-05-15

SimuliCore virtual operations layer add-ons & performance boosters.

## CLA3P Module

### New Features
- New enhanced virtual operations with template expressions.
- Sparse (csc) matrices now included in virtual operation layer.

### Changes
- Move dense linear solver class outside of the `dns` namespace.
- Rename dense linear solver class from `cla3p::LSolver<type>` to `cla3p::Lapack<type>`.

### Fixes
- Fix ABI compiler warning.


# [v1.2.0] - 2024-04-25

SimuliCore new version with copy constructor support & more efficient virtual operations.

## CLA3P Module

### New Features
- Copy constructor/assignment support for all entities.
- Enhanced virtual operations efficiency.
- Add property creation functions in Property class.

### Changes
- Remove functional multiplications that return new objects.
- Remove 'nz' argument from coo matrix constructors.
- [CLA3P-33](https://github.com/connorkauf/simulicore/issues/33) More efficient reconstruction of dense objects.

### Fixes
- Fix in documentation links.
- Fix in virtual outer product.


# [v1.1.0] - 2024-03-05

SimuliCore next version with various features, bug-fixes and patches.

## CLA3P Module

### New Features
- Vector dot product.
- Add sparse matrix utility class (coordinate format).
- Add sparse matrix class (compressed sparse column format).
- [CLA3P-25](https://github.com/connorkauf/simulicore/issues/25) Virtual Operations Implementation.
- [CLA3P-34](https://github.com/connorkauf/simulicore/issues/34) Implementation of sparse algebra.

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

