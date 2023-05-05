#!/bin/bash
EXEC_DIR="$PWD"
ROOT_DIR=`dirname $0`
cmake -S ${ROOT_DIR} -B ${ROOT_DIR}/build
cd ${ROOT_DIR}/build
make
make install
cd ${EXEC_DIR}
exit 0

