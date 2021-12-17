cmake_minimum_required(VERSION 3.20)
project(aed_proj_2021)

set(CMAKE_CXX_STANDARD 14)

add_executable(aed_proj_2021 src/main.cpp includes/constants.h includes/Exceptions.h
               src/Airport.cpp includes/Airport.h
               includes/BST.h
               src/Cart.cpp includes/Cart.h
               src/Client.cpp includes/Client.h
               src/Company.cpp includes/Company.h
               src/Flight.cpp includes/Flight.h
               src/Luggage.cpp includes/Luggage.h
               src/Plane.cpp includes/Plane.h
               src/Service.cpp includes/Service.h
               src/Ticket.cpp includes/Ticket.h
               src/Transport.cpp includes/Transport.h
               src/UserInterface.cpp includes/UserInterface.h
               src/Utils.cpp includes/Utils.h)

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
