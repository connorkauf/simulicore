set(CLA3P_DOCUMENTATION_INSTALL documentation/cla3p)

install(FILES Doxyfile DESTINATION ${CLA3P_DOCUMENTATION_INSTALL})
install(FILES DoxygenLayout.xml DESTINATION ${CLA3P_DOCUMENTATION_INSTALL})
install(FILES modules.dox DESTINATION ${CLA3P_DOCUMENTATION_INSTALL})
install(FILES tutorial.dox DESTINATION ${CLA3P_DOCUMENTATION_INSTALL})
install(FILES cla3pdoxygen.css DESTINATION ${CLA3P_DOCUMENTATION_INSTALL})
install(PROGRAMS sectionfixer.sh DESTINATION ${CLA3P_DOCUMENTATION_INSTALL})

install(FILES ${CLA3P_ROOT}/README.md DESTINATION ${CLA3P_DOCUMENTATION_INSTALL})

set(CLA3P_VERSION "${CMAKE_CURRENT_BINARY_DIR}/cla3pversion.dox")
file(WRITE ${CLA3P_VERSION} "PROJECT_NUMBER = \"v${CMAKE_PROJECT_VERSION}\"")
install(FILES ${CLA3P_VERSION} DESTINATION ${CLA3P_DOCUMENTATION_INSTALL})
