#-----------------------------------------------
# source setup
#-----------------------------------------------
set(CLA3P_SRC ${CLA3P_SRC}
	generic/meta1d.cpp
	generic/meta2d.cpp
	generic/matrix_meta.cpp
	generic/coord.cpp
	generic/tuple.cpp
	generic/guard.cpp
	generic/ownership.cpp
	generic/array2d.cpp
	PARENT_SCOPE)

set(CLA3P_GENERIC_HPP 
	meta1d.hpp
	meta2d.hpp
	matrix_meta.hpp
	coord.hpp
	tuple.hpp
	guard.hpp
	ownership.hpp
	array2d.hpp
	type_traits.hpp
	)

#-----------------------------------------------
# installation setup
#-----------------------------------------------
set(CLA3P_GENERIC_HPP_INSTALL include/cla3p/generic)

install(FILES ${CLA3P_GENERIC_HPP} DESTINATION ${CLA3P_GENERIC_HPP_INSTALL})
#-----------------------------------------------
# end
#-----------------------------------------------
