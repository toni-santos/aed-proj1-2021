cmake_minimum_required(VERSION 3.20)
project(aed_proj_2021)

set(CMAKE_CXX_STANDARD 14)

add_executable(aed_proj_2021 src/main.cpp includes/Plane.h includes/Flight.h src/Ticket.cpp includes/Ticket.h src/Flight.cpp)
