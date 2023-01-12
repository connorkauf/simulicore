#!/bin/bash
ROOT_DIR=`dirname $0`
rm -f ${ROOT_DIR}/install/lib/* 
rm -rf ${ROOT_DIR}/build/* ${ROOT_DIR}/build.ninja_*
cmake -GNinja -S ${ROOT_DIR} -B ${ROOT_DIR}/build
exit 0
