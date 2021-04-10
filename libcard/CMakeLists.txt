
project(libcard)


set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS 1)

add_library(card SHARED list/list.c display/display.c manipulate/manipulate.c types/types.c)