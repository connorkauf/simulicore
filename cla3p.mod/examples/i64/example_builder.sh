#!/bin/bash
ROOT_DIR=`dirname $0`
cmake -S ${ROOT_DIR} -B ${ROOT_DIR}/build -DCLA3P_USE_I64=true
cmake --build ${ROOT_DIR}/build/
cmake --install ${ROOT_DIR}/build/
exit 0

