#!/bin/bash
EXEC_DIR="$PWD"
ROOT_DIR=`dirname $0`
cd ${ROOT_DIR}/obj
ninja $@ && ninja install
cd ${EXEC_DIR}
exit 0
