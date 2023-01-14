#!/bin/bash

ROOT_DIR=`dirname $0`
CLA3P_LIB=${ROOT_DIR}/../lib

if [[ -z ${LD_LIBRARY_PATH} ]]; then
	export LD_LIBRARY_PATH=${CLA3P_LIB}
else
	export LD_LIBRARY_PATH=${LD_LIBRARY_PATH}:${CLA3P_LIB}
fi

exec ${ROOT_DIR}/example
