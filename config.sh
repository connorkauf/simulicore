#!/bin/bash
ROOT_DIR=`dirname $0`
rm -rf ${ROOT_DIR}/obj/*
rm -rf ${ROOT_DIR}/obj/build.ninja_*
rm -rf ${ROOT_DIR}/install/*
cmake -GNinja -S ${ROOT_DIR} -B ${ROOT_DIR}/obj
exit 0
