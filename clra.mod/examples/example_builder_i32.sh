#!/bin/bash
ROOT_DIR=`dirname $0`
BUILD_DIR=${ROOT_DIR}/i32/build
cmake -S ${ROOT_DIR} -B ${BUILD_DIR}
cmake --build ${BUILD_DIR}
cmake --install ${BUILD_DIR}
exit 0

