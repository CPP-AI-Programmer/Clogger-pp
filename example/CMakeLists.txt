cmake_minimum_required(VERSION 3.22.1) # my version 
project(Cloggerpp_test VERSION 1.0.0)

find_package(Cloggerpp)

add_executable(main ../main.cpp)
add_executable(tui ../tui.cpp)

target_link_libraries(main PUBLIC Cloggerpp)
target_link_libraries(tui PUBLIC Cloggerpp ncurses)
