#-----------------------------------------------
# source setup
#-----------------------------------------------
set(CLA3P_EXAMPLES_SRC
	ex01a_create_dense_vector.cpp
	ex01b_fill_dense_vector.cpp
	ex01c_create_dense_vector_from_aux_data.cpp
	ex01d_create_dense_random_vector.cpp
	ex01e_dense_vector_copy_move.cpp
	ex01f_dense_vector_shallow_copy.cpp
	ex01g_dense_vector_block_operations.cpp
	ex01h_dense_vector_algebra.cpp
	ex02a_create_dense_matrix.cpp
	ex02b_fill_dense_matrix.cpp
	ex02c_create_dense_matrix_with_property.cpp
	ex02d_create_dense_matrix_from_aux_data.cpp
	ex02e_create_dense_random_matrix.cpp
	ex02f_dense_matrix_copy_move.cpp
	ex02g_dense_matrix_shallow_copy.cpp
	ex02h_dense_matrix_block_operations.cpp
	ex02h_dense_matrix_column_operations.cpp
	ex02i_dense_matrix_algebra_part1.cpp
	ex02i_dense_matrix_algebra_part2.cpp
	ex02i_dense_matrix_algebra_part3.cpp
	ex02i_dense_matrix_algebra_part4.cpp
	ex03a_create_permutation_matrix.cpp
	ex03b_fill_permutation_matrix.cpp
	ex03c_create_identity_permutation_matrix.cpp
	ex03c_create_random_permutation_matrix.cpp
	ex03d_permute_vector.cpp
	ex03e_permute_matrix_part1.cpp
	ex03e_permute_matrix_part2.cpp
	ex03f_permute_permutations.cpp
	ex04a_using_guards_part1.cpp
	ex04a_using_guards_part2.cpp
	ex05a_solving_linear_systems_lu.cpp
	ex05b_solving_linear_systems_ldlt.cpp
	ex05c_solving_linear_systems_auto.cpp
	ex05d_solving_linear_systems_operators.cpp
	)

set(CLA3P_EXAMPLES_CMAKE cmake_list_install/CMakeLists.txt)

#-----------------------------------------------
# installation setup
#-----------------------------------------------
set(CLA3P_EXAMPLES_INSTALL examples/cla3p)

install(FILES ${CLA3P_EXAMPLES_SRC} DESTINATION ${CLA3P_EXAMPLES_INSTALL})
install(FILES ${CLA3P_EXAMPLES_CMAKE} DESTINATION ${CLA3P_EXAMPLES_INSTALL})

if(LINUX)
	if(CLA3P_USE_I64)
		install(PROGRAMS i64/example_builder.sh DESTINATION ${CLA3P_EXAMPLES_INSTALL})
	else()
		install(PROGRAMS i32/example_builder.sh DESTINATION ${CLA3P_EXAMPLES_INSTALL})
	endif()
endif()
#-----------------------------------------------
# end
#-----------------------------------------------
