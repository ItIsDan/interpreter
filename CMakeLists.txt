cmake_minimum_required(VERSION 3.5)

project(interpreter LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(interpreter main.cpp lexer.cpp lexer.h token.cpp token.h
parser.cpp parser.h)

install(TARGETS interpreter
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
