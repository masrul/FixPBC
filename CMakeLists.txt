######################################################################
# @author      : Masrul Huda (mail2masrul@gmail.com)
# @file        : CMakeLists
# @created     : Thursday Jun 30, 2022 19:52:24 CDT
######################################################################

cmake_minimum_required(VERSION 3.0)
set(CMAKE_C_COMPILER gcc)
set(CMAKE_CXX_COMPILER g++)

project("test_libgmxtraj")
set(CMAKE_VERBOSE_MAKEFILE ON)

# Optimization flag 
if ("${CMAKE_CXX_COMPILER_ID}" MATCHES "Clang")
    set(CMAKE_C_FLAGS "-O2 -Wno-incompatible-function-pointer-types")
    set(CMAKE_CXX_FLAGS "-O2 -Wall  -std=c++17")
elseif ("${CMAKE_CXX_COMPILER_ID}" STREQUAL "GNU")
    set(CMAKE_C_FLAGS "-O2 -Wno-incompatible-function-pointer-types")
    set(CMAKE_CXX_FLAGS "-O2  -std=c++17")
endif()


set(ENV{PKG_CONFIG_PATH} "$ENV{PKG_CONFIG_PATH}:/home/mmh568/software/libgmxtraj/lib/pkgconfig")
include(FindPkgConfig)
pkg_search_module(GMXTRAJ REQUIRED libgmxtraj)


include_directories(${GMXTRAJ_INCLUDE_DIRS})
include_directories("./include/")
link_directories (${GMXTRAJ_LIBRARY_DIRS})
file(GLOB SOURCES "src/*.cpp")
add_executable("fix_pbc" ${SOURCES})
target_link_libraries("fix_pbc" ${GMXTRAJ_LIBRARIES})
