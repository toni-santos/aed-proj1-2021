cmake_minimum_required(VERSION 3.20)
project(aed_proj_2021)

set(CMAKE_CXX_STANDARD 14)

add_executable(aed_proj_2021 src/main.cpp src/Plane.cpp includes/Plane.h src/Flight.cpp includes/Flight.h src/Ticket.cpp includes/Ticket.h)
