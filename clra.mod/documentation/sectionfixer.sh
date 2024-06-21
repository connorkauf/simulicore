#!/bin/bash

ROOT_DIR=`dirname $0`

sed -i 's/#tutorial_datatypes\>//g' ${ROOT_DIR}/html/*.js
sed -i 's/#tutorial_vectors\>//g' ${ROOT_DIR}/html/*.js
sed -i 's/#tutorial_vectors_dense\>//g' ${ROOT_DIR}/html/*.js
sed -i 's/#tutorial_property\>//g' ${ROOT_DIR}/html/*.js
sed -i 's/#tutorial_matrices\>//g' ${ROOT_DIR}/html/*.js
sed -i 's/#tutorial_matrices_dense\>//g' ${ROOT_DIR}/html/*.js
sed -i 's/#tutorial_matrices_sparse\>//g' ${ROOT_DIR}/html/*.js
sed -i 's/#tutorial_guard\>//g' ${ROOT_DIR}/html/*.js
sed -i 's/#tutorial_assign\>//g' ${ROOT_DIR}/html/*.js
sed -i 's/#tutorial_block_ops\>//g' ${ROOT_DIR}/html/*.js
sed -i 's/#tutorial_perm\>//g' ${ROOT_DIR}/html/*.js
sed -i 's/#tutorial_perm_matrix\>//g' ${ROOT_DIR}/html/*.js
sed -i 's/#tutorial_perm_ops\>//g' ${ROOT_DIR}/html/*.js
sed -i 's/#tutorial_linsol\>//g' ${ROOT_DIR}/html/*.js
sed -i 's/#tutorial_linsol_lapack\>//g' ${ROOT_DIR}/html/*.js
sed -i 's/#tutorial_linsol_pardiso\>//g' ${ROOT_DIR}/html/*.js

exit 0
