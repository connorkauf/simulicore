#-----------------------------------------------
# source setup
#-----------------------------------------------
set(CLA3P_EXAMPLES_SRC
	ex00_property_create.cpp
	ex01a_dense_vector_create.cpp
	ex01b_dense_vector_fill.cpp
	ex01c_dense_vector_create_from_aux_data.cpp
	ex01d_dense_vector_create_random.cpp
	ex01e_dense_vector_copy.cpp
	ex01f_dense_vector_move.cpp
	ex01g_dense_vector_block_operations.cpp
	ex01h_dense_vector_shallow_copy.cpp
	ex01i_dense_vector_algebra_scale.cpp
	ex01j_dense_vector_algebra_add.cpp
	ex01k_dense_vector_algebra_dot.cpp
	ex02a_dense_matrix_create.cpp
	ex02b_dense_matrix_fill.cpp
	ex02c_dense_matrix_create_with_property.cpp
	ex02d_dense_matrix_create_from_aux_data.cpp
	ex02e_dense_matrix_create_random.cpp
	ex02f_dense_matrix_copy.cpp
	ex02g_dense_matrix_move.cpp
	ex02h_dense_matrix_shallow_copy.cpp
	ex02i_dense_matrix_block_operations.cpp
	ex02j_dense_matrix_column_operations.cpp
	ex02k_dense_matrix_algebra_scale.cpp
	ex02l_dense_matrix_algebra_add.cpp
	ex02m_dense_matrix_algebra_vmult.cpp
	ex02n_dense_matrix_algebra_mmult.cpp
	ex02o_dense_matrix_algebra_mtmult.cpp
	ex03a_permutation_matrix_create.cpp
	ex03b_permutation_matrix_fill.cpp
	ex03c_permutation_matrix_create_identity.cpp
	ex03d_permutation_matrix_create_random.cpp
	ex03e_permutation_matrix_permute_vector.cpp
	ex03f_permutation_matrix_permute_matrix.cpp
	ex03g_permutation_matrix_permute_matrix_symmetric.cpp
	ex03h_permutation_matrix_permute_permutation_matrix.cpp
	ex04a_guard_const_vector.cpp
	ex04b_guard_const_matrix.cpp
	ex05a_solving_linear_systems_lu.cpp
	ex05b_solving_linear_systems_ldlt.cpp
	ex05c_solving_linear_systems_auto.cpp
	ex05d_solving_linear_systems_operators.cpp
	ex06a_sparse_matrix_create.cpp
	ex06c_sparse_matrix_create_with_property.cpp
	ex06d_sparse_matrix_create_from_aux_data.cpp
	ex06b_sparse_matrix_fill.cpp
	ex06k_sparse_matrix_algebra_scale.cpp
	ex06l_sparse_matrix_algebra_add.cpp
	ex06m_sparse_matrix_algebra_vmult.cpp
	ex06n_sparse_matrix_algebra_mmult.cpp
	ex07a_solving_sparse_linear_systems_lu.cpp
	ex07b_solving_sparse_linear_systems_llt.cpp
	ex07c_solving_sparse_linear_systems_ldlt.cpp
	ex07d_solving_sparse_linear_systems_operators.cpp
	ex07e_solving_sparse_linear_systems_auto.cpp
	ex08a_qr_decomposition.cpp
	ex08b_sv_decomposition.cpp
	)

#-----------------------------------------------
# installation setup
#-----------------------------------------------
set(CLA3P_EXAMPLES_INSTALL examples/cla3p/src)

install(FILES ${CLA3P_EXAMPLES_SRC} DESTINATION ${CLA3P_EXAMPLES_INSTALL})

#-----------------------------------------------
# end
#-----------------------------------------------
