#!/bin/bash

ROOT_DIR=`dirname $0`

sed -i 's/#clra_tutorial_matrices\>//g' ${ROOT_DIR}/html/*.js
sed -i 's/#clra_tutorial_matrices_lowrank\>//g' ${ROOT_DIR}/html/*.js
sed -i 's/#clra_tutorial_matrices_hybrid\>//g' ${ROOT_DIR}/html/*.js

exit 0
