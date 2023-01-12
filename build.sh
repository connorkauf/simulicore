#!/bin/bash
EXEC_DIR="$PWD"
ROOT_DIR=`dirname $0`
cd ${ROOT_DIR}/build
ninja && ninja install
cd ${EXEC_DIR}
exit 0
