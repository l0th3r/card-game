cmake_minimum_required(VERSION 3.20)

project(cardgame)

set(LIBLIST ../liblist CACHE PATH "Path of libcard folder")
set(LIBCARDS ../libcard CACHE PATH "Path of libcard folder")
set(RAYLIB ../raylib CACHE PATH "Path of raylib folder")

set (LIBS liblist libcards raylib)

if(WIN32)
    set (LIBS ${LIBS} winmm)
endif()

add_subdirectory(${LIBCARDS} ${LIBCARDS})

add_executable(cardgame cardgame.c DBtn.c DCard.c DDeck.c DDisc.c DPlate.c frame_container.c mouse_handler.c)

if (WIN32)
    add_custom_command (
        TARGET cardgame POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${LIBCARDS}/$<CONFIGURATION>/libcards.dll"
        "${CMAKE_CURRENT_BINARY_DIR}/$<CONFIGURATION>"
    )
    add_custom_command (
        TARGET cardgame POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        "${LIBLIST}/$<CONFIGURATION>/liblist.dll"
        "${CMAKE_CURRENT_BINARY_DIR}/$<CONFIGURATION>"
    )
endif()

target_include_directories(cardgame PUBLIC ${LIBLIST} ${LIBCARDS} ${RAYLIB}/include)

target_link_directories(cardgame PUBLIC ${LIBLIST} ${LIBCARDS} ${RAYLIB}/lib)

target_link_libraries(cardgame PUBLIC ${LIBS})