#!/bin/bash
ROOT_DIR=`dirname $0`
rm -rf ${ROOT_DIR}/build/*
rm -rf ${ROOT_DIR}/build/build.ninja_*
rm -rf ${ROOT_DIR}/install/*
cmake -GNinja -S ${ROOT_DIR} -B ${ROOT_DIR}/build $@
exit 0
