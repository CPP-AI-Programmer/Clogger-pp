cmake_minimum_required(VERSION 3.22.1) # my version 
project(Cloggerpp_test VERSION 1.0.0)

include(FetchContent)

FetchContent_Declare(
    Clogger_pp 
    GIT_REPOSITORY https://github.com/CPP-AI-Programmer/Clogger-pp.git
    GIT_TAG master) 
FetchContent_MakeAvailable(Clogger_pp)

add_executable(main main.cpp)

target_link_libraries(main PUBLIC Cloggerpp::Cloggerpp)
