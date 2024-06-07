set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)

if(${SIMULICORE_CMAKE_LINUX})
	if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
		if(${SIMULICORE_FULL_INSTALL})
			add_compile_options(-Werror)
			add_compile_options(-Wpedantic)
		endif()
		add_compile_options(-m64)
		add_compile_options(-Wall)
		add_compile_options(-Wextra)
		add_compile_options(-Wshadow)
		add_compile_options(-Wmissing-format-attribute)
		add_compile_options(-fdiagnostics-color=always)
	endif()
endif()

if(${SIMULICORE_CMAKE_MACOS})
	execute_process(COMMAND brew --prefix
		OUTPUT_STRIP_TRAILING_WHITESPACE
		OUTPUT_VARIABLE BREW_PREFIX_DIR
		RESULTS_VARIABLE BREW_PREFIX_COMMAND_RET)
	if(${BREW_PREFIX_COMMAND_RET} EQUAL "0")
		message(STATUS "Homebrew directory: ${BREW_PREFIX_DIR}")
	else()
		unset(BREW_PREFIX_DIR)
		message(WARNING "Could not find Homebrew directory")
	endif()
endif()

# TODO: add options for all compilers
