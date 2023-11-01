#!/bin/bash
ROOT_DIR=`dirname $0`
BUILD_DIR=${ROOT_DIR}/i64/build
cmake -S ${ROOT_DIR} -B ${BUILD_DIR} -DCLA3P_EXAMPLES_I64=true
cmake --build ${BUILD_DIR}
cmake --install ${BUILD_DIR}
exit 0

