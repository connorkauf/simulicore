#!/bin/bash
EXEC_DIR="$PWD"
ROOT_DIR=`dirname $0`
cmake -S ${ROOT_DIR} -B ${ROOT_DIR}/build -DCLA3P_USE_I64=true
cd ${ROOT_DIR}/build
make
make install
cd ${EXEC_DIR}
exit 0

