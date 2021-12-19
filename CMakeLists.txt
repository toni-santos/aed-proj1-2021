cmake_minimum_required(VERSION 3.16)
project(aed_proj_2021
        VERSION 1.0
        LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)

add_executable(aed_proj_2021           src/main.cpp
               src/Airport.cpp         src/Cart.cpp
               src/Client.cpp          src/Company.cpp
               src/Flight.cpp          src/Luggage.cpp
               src/Plane.cpp           src/Service.cpp
               src/Ticket.cpp          src/Transport.cpp
               src/UserInterface.cpp   src/Utils.cpp)

add_executable(aed_proj_2021_no_ansi   src/main.cpp
               src/Airport.cpp         src/Cart.cpp
               src/Client.cpp          src/Company.cpp
               src/Flight.cpp          src/Luggage.cpp
               src/Plane.cpp           src/Service.cpp
               src/Ticket.cpp          src/Transport.cpp
               src/UserInterface.cpp   src/Utils.cpp)
target_compile_definitions(aed_proj_2021_no_ansi PUBLIC NO_ANSI)

include_directories(aed_proj_2021 includes/)
include_directories(aed_proj_2021_no_ansi includes/)

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
