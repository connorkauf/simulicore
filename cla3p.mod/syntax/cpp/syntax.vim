"---------------------------------------------------------------------------

syn keyword cTypeCustomDatatype MKL_INT
syn keyword cTypeCustomDatatype MKL_UINT
syn keyword cTypeCustomDatatype MKL_Complex8
syn keyword cTypeCustomDatatype MKL_Complex16

syn keyword cTypeCustomDatatype nint_t
syn keyword cTypeCustomDatatype int_t
syn keyword cTypeCustomDatatype uint_t
syn keyword cTypeCustomDatatype real4_t
syn keyword cTypeCustomDatatype real_t
syn keyword cTypeCustomDatatype complex8_t
syn keyword cTypeCustomDatatype complex_t
syn keyword cTypeCustomDatatype bulk_t

syn keyword cTypeCustomDatatype prop_t
syn keyword cTypeCustomDatatype uplo_t
syn keyword cTypeCustomDatatype op_t
syn keyword cTypeCustomDatatype side_t
syn keyword cTypeCustomDatatype diag_t
syn keyword cTypeCustomDatatype dup_t
syn keyword cTypeCustomDatatype decomp_t
syn keyword cTypeCustomDatatype svpolicy_t
syn keyword cTypeCustomDatatype qpolicy_t
syn keyword cTypeCustomDatatype qrtrans_t
syn keyword cTypeCustomDatatype mtype_t
syn keyword cTypeCustomDatatype phase_t
syn keyword cTypeCustomDatatype reorder_t
syn keyword cTypeCustomDatatype perm_t
syn keyword cTypeCustomDatatype pivot_t

syn keyword cTypeCustomDatatype Property
syn keyword cTypeCustomDatatype Operation
syn keyword cTypeCustomDatatype Printer

syn keyword cTypeCustomDatatype Exception
syn keyword cTypeCustomDatatype NoConsistency
syn keyword cTypeCustomDatatype InvalidOp
syn keyword cTypeCustomDatatype OutOfMemory
syn keyword cTypeCustomDatatype OutOfBounds

syn keyword cTypeCustomDatatype TypeTraits

syn keyword cTypeCustomDatatype Ownership
syn keyword cTypeCustomDatatype Meta1D
syn keyword cTypeCustomDatatype Meta2D
syn keyword cTypeCustomDatatype MatrixMeta
syn keyword cTypeCustomDatatype Guard
syn keyword cTypeCustomDatatype Coord
syn keyword cTypeCustomDatatype Tuple
syn keyword cTypeCustomDatatype TupleVec
syn keyword cTypeCustomDatatype HeapBuffer
syn keyword cTypeCustomDatatype ThreadManager
syn keyword cTypeCustomDatatype Timer
syn keyword cTypeCustomDatatype RealTimer

syn keyword cTypeCustomDatatype VirtualEntity
syn keyword cTypeCustomDatatype VirtualParams
syn keyword cTypeCustomDatatype VirtualRowVec
syn keyword cTypeCustomDatatype VirtualObject
syn keyword cTypeCustomDatatype VirtualVector
syn keyword cTypeCustomDatatype VirtualMatrix
syn keyword cTypeCustomDatatype VirtualProd
syn keyword cTypeCustomDatatype VirtualSum

syn keyword cTypeCustomDatatype PxMatrix
syn keyword cTypeCustomDatatype PiMatrix
syn keyword cTypeCustomDatatype PuMatrix

syn keyword cTypeCustomDatatype XxObject
syn keyword cTypeCustomDatatype XiVector XxVector RxVector CxVector
syn keyword cTypeCustomDatatype RdVector RfVector CdVector CfVector
syn keyword cTypeCustomDatatype XxMatrix RxMatrix CxMatrix
syn keyword cTypeCustomDatatype RdMatrix RfMatrix CdMatrix CfMatrix

syn keyword cTypeCustomDatatype LapackBase
syn keyword cTypeCustomDatatype LapackAuto
syn keyword cTypeCustomDatatype LapackLLt
syn keyword cTypeCustomDatatype LapackLDLt
syn keyword cTypeCustomDatatype LapackLU
syn keyword cTypeCustomDatatype LapackCompleteLU

syn keyword cTypeCustomDatatype ImmutableParams
syn keyword cTypeCustomDatatype GlobalParams
syn keyword cTypeCustomDatatype AnalysisParams
syn keyword cTypeCustomDatatype DecompParams
syn keyword cTypeCustomDatatype SolveParams
syn keyword cTypeCustomDatatype PardisoBase
syn keyword cTypeCustomDatatype PardisoAuto
syn keyword cTypeCustomDatatype PardisoLLt
syn keyword cTypeCustomDatatype PardisoLDLt
syn keyword cTypeCustomDatatype PardisoLU
syn keyword cTypeCustomDatatype PardisoSymmetricLU

syn keyword cTypeCustomDatatype DefaultSVD
syn keyword cTypeCustomDatatype DefaultQR

hi cTypeCustomDatatype ctermfg=lightgreen guifg=darkblue

"---------------------------------------------------------------------------

syn keyword cTypeCustomConst NONE AUTO ENUMMAX
syn keyword cTypeCustomConst SIZEKB SIZEMB SIZEGB SIZETB
syn keyword cTypeCustomConst MKL_ALLOC_ALIGNMENT

hi cTypeCustomConst ctermfg=darkmagenta guifg=darkblue

"---------------------------------------------------------------------------

syn keyword cTypeCustomTemplate T_Int
syn keyword cTypeCustomTemplate T_Scalar
syn keyword cTypeCustomTemplate T_RScalar
syn keyword cTypeCustomTemplate T_Object
syn keyword cTypeCustomTemplate T_Vector
syn keyword cTypeCustomTemplate T_RVector
syn keyword cTypeCustomTemplate T_Matrix
syn keyword cTypeCustomTemplate T_RMatrix
syn keyword cTypeCustomTemplate T_DnsMatrix
syn keyword cTypeCustomTemplate T_CscMatrix
syn keyword cTypeCustomTemplate T_CooMatrix
syn keyword cTypeCustomTemplate T_Rhs
syn keyword cTypeCustomTemplate T_Lhs
syn keyword cTypeCustomTemplate T_RhsMatrix
syn keyword cTypeCustomTemplate T_LhsMatrix
syn keyword cTypeCustomTemplate T_Virtual

hi cTypeCustomTemplate ctermfg=lightcyan guifg=darkblue

"---------------------------------------------------------------------------
syn keyword cTypeCustomNSpace std

syn keyword cTypeCustomNSpace cla3p
syn keyword cTypeCustomNSpace cmpi

syn keyword cTypeCustomNSpace mkl
syn keyword cTypeCustomNSpace armpl
syn keyword cTypeCustomNSpace blas
syn keyword cTypeCustomNSpace lapack
syn keyword cTypeCustomNSpace pardiso

syn keyword cTypeCustomNSpace mt
syn keyword cTypeCustomNSpace blk
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
