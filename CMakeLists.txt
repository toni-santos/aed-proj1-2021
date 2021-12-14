cmake_minimum_required(VERSION 3.20)
project(aed_proj_2021)

set(CMAKE_CXX_STANDARD 14)

add_executable(aed_proj_2021 src/main.cpp includes/Plane.h includes/Flight.h src/Ticket.cpp includes/Ticket.h src/Flight.cpp src/Client.cpp includes/Client.h src/Service.cpp includes/Service.h src/Menu.cpp includes/Menu.h src/Company.cpp includes/Company.h src/Utils.cpp includes/Utils.h includes/constants.h)

# Doxygen Build
find_package(Doxygen)
if(DOXYGEN_FOUND)
    set(BUILD_DOC_DIR "${CMAKE_SOURCE_DIR}/docs")
    if(NOT EXISTS "${BUILD_DOC_DIR}")
        file(MAKE_DIRECTORY "${BUILD_DOC_DIR}")
    endif()

    set(DOXYGEN_IN "${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile")
    set(DOXYGEN_OUT "${CMAKE_CURRENT_BINARY_DIR}/Doxyfile")
    configure_file("${DOXYGEN_IN}" "${DOXYGEN_OUT}" @ONLY)
    message("Doxygen build started") 
    add_custom_target(Doxygen ALL 
            COMMAND "${DOXYGEN_EXECUTABLE}" "${DOXYGEN_OUT}" 
            WORKING_DIRECTORY "${CMAKE_CURRENT_BINARY_DIR}" 
            COMMENT "Generating API documentation with Doxygen" 
            VERBATIM) 
else(DOXYGEN_FOUND) 
    message("Doxygen needs to be installed to generate the documentation.") 
endif(DOXYGEN_FOUND)
