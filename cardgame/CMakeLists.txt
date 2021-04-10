cmake_minimum_required(VERSION 3.16)

project(cardgame)

set(LIBCARD ../libcard CACHE PATH "Path of libcard folder")
set(RAYLIB ../raylib CACHE PATH "Path of raylib folder")

set (LIBS card raylib)
if (WIN32)
    add_custom_command (
        TARGET cardgame POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${LIBCARD}/$<CONFIGURATION>/card.dll"
        "${CMAKE_CURRENT_BINARY_DIR}/$<CONFIGURATION>"
    )
endif()

add_subdirectory(${LIBCARD} ${LIBCARD})

add_executable(cardgame cardgame.c)

target_include_directories(cardgame PUBLIC ${LIBCARD} ${RAYLIB}/include)

target_link_directories(cardgame PUBLIC ${LIBCARD} ${RAYLIB}/lib)

target_link_libraries(cardgame PUBLIC ${LIBS})
