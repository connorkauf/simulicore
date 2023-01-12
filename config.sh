#!/bin/bash
ROOT_DIR=`dirname $0`
rm -rf ${ROOT_DIR}/build/*
rm -rf ${ROOT_DIR}/build.ninja_*
rm -rf ${ROOT_DIR}/install/*
rm -rf ${ROOT_DIR}/docs/*
cmake -GNinja -S ${ROOT_DIR} -B ${ROOT_DIR}/build
exit 0
