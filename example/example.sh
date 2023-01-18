#!/bin/bash
ROOT_DIR=`dirname $0`

CLA3P_LIB=${ROOT_DIR}/../lib
CMPI_LIB=${ROOT_DIR}/../lib

MKL_LIB=/home/konstantinos/Development/3rd/intel/oneapi/mkl/2023.0.0/lib/intel64
IOMP5_LIB=/home/konstantinos/Development/3rd/intel/oneapi/compiler/2023.0.0/linux/compiler/lib/intel64_lin

if [[ -z ${LD_LIBRARY_PATH} ]]; then
	export LD_LIBRARY_PATH=${CLA3P_LIB}:${CMPI_LIB}:${MKL_LIB}:${IOMP5_LIB}
else
	export LD_LIBRARY_PATH=${LD_LIBRARY_PATH}:${CLA3P_LIB}:${CMPI_LIB}:${MKL_LIB}:${IOMP5_LIB}
fi

exec ${ROOT_DIR}/example
