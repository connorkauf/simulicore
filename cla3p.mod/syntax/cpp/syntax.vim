"---------------------------------------------------------------------------

syn keyword cTypeCustomDatatype MKL_INT MKL_UINT MKL_Complex8 MKL_Complex16
syn keyword cTypeCustomDatatype nint_t int_t uint_t real4_t real_t complex8_t complex_t bulk_t
syn keyword cTypeCustomDatatype prop_t uplo_t op_t side_t diag_t dup_t
syn keyword cTypeCustomDatatype Property Operation
syn keyword cTypeCustomDatatype Printer
syn keyword cTypeCustomDatatype Exception NoConsistency InvalidOp Overflow OutOfMemory OutOfBounds

syn keyword cTypeCustomDatatype TypeTraits

syn keyword cTypeCustomDatatype Ownership
syn keyword cTypeCustomDatatype Meta1D Meta2D MatrixMeta
syn keyword cTypeCustomDatatype Array2D
syn keyword cTypeCustomDatatype Guard
syn keyword cTypeCustomDatatype Coord Tuple TupleVec
syn keyword cTypeCustomDatatype VirtualEntity
syn keyword cTypeCustomDatatype VirtualParams VirtualRowVec VirtualObject VirtualVector VirtualMatrix
syn keyword cTypeCustomDatatype VirtualProd
syn keyword cTypeCustomDatatype VirtualSum
syn keyword cTypeCustomDatatype PxMatrix PiMatrix PuMatrix
syn keyword cTypeCustomDatatype XxObject
syn keyword cTypeCustomDatatype XiVector XxVector RxVector CxVector
syn keyword cTypeCustomDatatype RdVector RfVector CdVector CfVector
syn keyword cTypeCustomDatatype XxMatrix RxMatrix CxMatrix
syn keyword cTypeCustomDatatype RdMatrix RfMatrix CdMatrix CfMatrix
syn keyword cTypeCustomDatatype RdUMatrix RfUMatrix CdUMatrix CfUMatrix

syn keyword cTypeCustomDatatype LapackBase LapackAuto LapackLLt LapackLDLt LapackLU LapackCompleteLU

hi cTypeCustomDatatype ctermfg=lightgreen guifg=darkblue

"---------------------------------------------------------------------------

syn keyword cTypeCustomConst NONE AUTO ENUMMAX
syn keyword cTypeCustomConst SIZEKB SIZEMB SIZEGB SIZETB
syn keyword cTypeCustomConst MKL_ALLOC_ALIGNMENT

hi cTypeCustomConst ctermfg=darkmagenta guifg=darkblue

"---------------------------------------------------------------------------

syn keyword cTypeCustomTemplate T_Int T_PrmInt T_CscInt
syn keyword cTypeCustomTemplate T_Scalar T_RScalar
syn keyword cTypeCustomTemplate T_Return
syn keyword cTypeCustomTemplate T_Object
syn keyword cTypeCustomTemplate T_Vector T_RVector
syn keyword cTypeCustomTemplate T_Matrix T_RMatrix T_DnsMatrix T_CscMatrix
syn keyword cTypeCustomTemplate T_Rhs T_Lhs T_RhsMatrix T_LhsMatrix
syn keyword cTypeCustomTemplate T_Virtual

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
syn keyword cTypeCustomNSpace coo
syn keyword cTypeCustomNSpace prm

syn keyword cTypeCustomNSpace arith
syn keyword cTypeCustomNSpace err
syn keyword cTypeCustomNSpace msg
syn keyword cTypeCustomNSpace ops

hi cTypeCustomNSpace ctermfg=yellow guifg=darkblue

"---------------------------------------------------------------------------

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
