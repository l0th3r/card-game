cmake_minimum_required(VERSION 3.20)

project(liblist)

set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS 1)

add_library(liblist SHARED list.c)