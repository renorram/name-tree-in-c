cmake_minimum_required(VERSION 2.6)
project(Namelist)


add_library(tree tree.c tree.h)
add_library(reader reader.c reader.h)
add_library(name_tree name_tree.c name_tree.h)
add_executable(main main.c)
target_link_libraries(main  name_tree reader tree)

if ( CMAKE_COMPILER_IS_GNUCC )
    target_compile_options(main PRIVATE "-Wall")
endif()
