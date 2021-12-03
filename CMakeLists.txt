cmake_minimum_required(VERSION 3.20)
project(aed_proj_2021)

set(CMAKE_CXX_STANDARD 14)

add_executable(aed_proj_2021 src/main.cpp includes/Plane.h includes/Flight.h src/Ticket.cpp includes/Ticket.h src/Flight.cpp src/Client.cpp includes/Client.h src/Service.cpp includes/Service.h src/Menu.cpp includes/Menu.h src/Company.cpp includes/Company.h src/Utils.cpp includes/Utils.h includes/constants.h)
