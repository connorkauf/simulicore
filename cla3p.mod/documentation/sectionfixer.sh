#!/bin/bash

ROOT_DIR=`dirname $0`

sed -i 's/#cla3p_tutorial_datatypes\>//g' ${ROOT_DIR}/html/*.js
sed -i 's/#cla3p_tutorial_vectors\>//g' ${ROOT_DIR}/html/*.js
sed -i 's/#cla3p_tutorial_vectors_dense\>//g' ${ROOT_DIR}/html/*.js
sed -i 's/#cla3p_tutorial_property\>//g' ${ROOT_DIR}/html/*.js
sed -i 's/#cla3p_tutorial_matrices\>//g' ${ROOT_DIR}/html/*.js
sed -i 's/#cla3p_tutorial_matrices_dense\>//g' ${ROOT_DIR}/html/*.js
sed -i 's/#cla3p_tutorial_matrices_sparse\>//g' ${ROOT_DIR}/html/*.js
sed -i 's/#cla3p_tutorial_guard\>//g' ${ROOT_DIR}/html/*.js
sed -i 's/#cla3p_tutorial_assign\>//g' ${ROOT_DIR}/html/*.js
sed -i 's/#cla3p_tutorial_block_ops\>//g' ${ROOT_DIR}/html/*.js
sed -i 's/#cla3p_tutorial_perm\>//g' ${ROOT_DIR}/html/*.js
sed -i 's/#cla3p_tutorial_perm_matrix\>//g' ${ROOT_DIR}/html/*.js
sed -i 's/#cla3p_tutorial_perm_ops\>//g' ${ROOT_DIR}/html/*.js
sed -i 's/#cla3p_tutorial_linsol\>//g' ${ROOT_DIR}/html/*.js
sed -i 's/#cla3p_tutorial_linsol_lapack\>//g' ${ROOT_DIR}/html/*.js
sed -i 's/#cla3p_tutorial_linsol_pardiso\>//g' ${ROOT_DIR}/html/*.js
sed -i 's/#cla3p_tutorial_qr\>//g' ${ROOT_DIR}/html/*.js
sed -i 's/#cla3p_tutorial_svd\>//g' ${ROOT_DIR}/html/*.js

exit 0
