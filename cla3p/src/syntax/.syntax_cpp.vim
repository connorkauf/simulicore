"---------------------------------------------------------------------------

syn keyword cTypeCustomDatatype MKL_INT MKL_UINT MKL_Complex8 MKL_Complex16
syn keyword cTypeCustomDatatype nint_t int_t uint_t real4_t real_t complex8_t complex_t bulk_t
syn keyword cTypeCustomDatatype status_t Status
syn keyword cTypeCustomDatatype prop_t uplo_t op_t dup_t
syn keyword cTypeCustomDatatype Property Operation
syn keyword cTypeCustomDatatype Printer
syn keyword cTypeCustomDatatype Exception NoConsistency InvalidOp Overflow OutOfMemory OutOfBounds

syn keyword cTypeCustomDatatype BasicTypeTraits

syn keyword cTypeCustomDatatype Guard
syn keyword cTypeCustomDatatype Ownership
syn keyword cTypeCustomDatatype Array2D
syn keyword cTypeCustomDatatype PxMatrix PiMatrix PuMatrix
syn keyword cTypeCustomDatatype XxObject
syn keyword cTypeCustomDatatype XxVector RxVector CxVector RdVector RfVector CdVector CfVector
syn keyword cTypeCustomDatatype XxMatrix RxMatrix CxMatrix RdMatrix RfMatrix CdMatrix CfMatrix

syn keyword cTypeCustomDatatype LSolverBase LSolverAuto LSolverLLt LSolverLDLt LSolverLU LSolverCompleteLU

hi cTypeCustomDatatype ctermfg=lightgreen guifg=darkblue

"---------------------------------------------------------------------------

syn keyword cTypeCustomConst NONE AUTO ENUMMAX
syn keyword cTypeCustomConst SIZEKB SIZEMB SIZEGB SIZETB
syn keyword cTypeCustomConst MKL_ALLOC_ALIGNMENT
syn keyword cTypeCustomConst GENERAL SYMMETRIC HERMITIAN TRIANGULAR SKEW
syn keyword cTypeCustomConst DNS_VECTOR DNS_MATRIX CSC_VECTOR CSC_MATRIX
syn keyword cTypeCustomConst INT UINT REAL COMPLEX
syn keyword cTypeCustomConst SINGLE DOUBLE
syn keyword cTypeCustomConst SUM PROD AMAX AMIN

hi cTypeCustomConst ctermfg=darkmagenta guifg=darkblue

"---------------------------------------------------------------------------

syn keyword cTypeCustomTemplate T_Int
syn keyword cTypeCustomTemplate T_Scalar T_RScalar
syn keyword cTypeCustomTemplate T_Object
syn keyword cTypeCustomTemplate T_Vector T_RVector
syn keyword cTypeCustomTemplate T_Matrix T_RMatrix

hi cTypeCustomTemplate ctermfg=lightcyan guifg=darkblue

"---------------------------------------------------------------------------
syn keyword cTypeCustomNSpace std

syn keyword cTypeCustomNSpace cla3p
syn keyword cTypeCustomNSpace cmpi

syn keyword cTypeCustomNSpace mkl
syn keyword cTypeCustomNSpace blas
syn keyword cTypeCustomNSpace lapack

syn keyword cTypeCustomNSpace bulk
syn keyword cTypeCustomNSpace dns
syn keyword cTypeCustomNSpace csc
syn keyword cTypeCustomNSpace lrk

syn keyword cTypeCustomNSpace msg
syn keyword cTypeCustomNSpace ops
syn keyword cTypeCustomNSpace tests

hi cTypeCustomNSpace ctermfg=yellow guifg=darkblue

"---------------------------------------------------------------------------

syn keyword cTypeCustomFunY Warning WarningNoReach
syn keyword cTypeCustomFunR Error ErrorNoReach
syn keyword cTypeCustomFunR ERROR_DIM ERROR_PTR ERROR_LD ERROR_PROP ERROR_PRSQ ERROR_EMPTY

syn keyword cTypeCustomFunR XxObjectTmpl XxObjectTlst
syn keyword cTypeCustomFunR XxVectorTmpl XxVectorTlst
syn keyword cTypeCustomFunR RxVectorTmpl RxVectorTlst
syn keyword cTypeCustomFunR CxVectorTmpl CxVectorTlst
syn keyword cTypeCustomFunR XxMatrixTmpl XxMatrixTlst
syn keyword cTypeCustomFunR RxMatrixTmpl RxMatrixTlst
syn keyword cTypeCustomFunR CxMatrixTmpl CxMatrixTlst

hi cTypeCustomFunY ctermfg=yellow guifg=darkblue
hi cTypeCustomFunR ctermfg=red    guifg=darkblue

"---------------------------------------------------------------------------
