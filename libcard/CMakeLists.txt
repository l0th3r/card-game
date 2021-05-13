cmake_minimum_required(VERSION 3.20)

project(libcard)
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS 1)

set(LIBLIST ../liblist CACHE PATH "Path of libcard folder")

add_subdirectory(${LIBLIST} ${LIBLIST})

add_library(libcards SHARED display/display.c manipulate/manipulate.c types/types.c)

if (WIN32)
    add_custom_command (
        TARGET libcards POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${LIBLIST}/$<CONFIGURATION>/liblist.dll"
        "${CMAKE_CURRENT_BINARY_DIR}/$<CONFIGURATION>"
    )
endif()

target_include_directories(libcards PUBLIC ${LIBLIST})

target_link_directories(libcards PUBLIC ${LIBLIST})

target_link_libraries(libcards PUBLIC liblist)