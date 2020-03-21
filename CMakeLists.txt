cmake_minimum_required(VERSION 3.8)
project(CleanRanges)

include(cmake/UnityBuild.cmake)
include(cmake/SourceGroup.cmake)

# =========================================
# global options


# =========================================
# define library

file(GLOB_RECURSE SOURCES "src/*.cc" "src/*.hh")

arcana_source_group(SOURCES)

add_library(clean-ranges STATIC ${SOURCES})

target_include_directories(clean-ranges PUBLIC src/)

target_link_libraries(clean-ranges PUBLIC
    clean-core
    typed-geometry
)

# =========================================
# set up compile flags

if (MSVC)
    target_compile_options(clean-ranges PUBLIC /MP)
else()
    target_compile_options(clean-ranges PRIVATE -Wall -fPIC)
    target_link_libraries(clean-ranges PUBLIC -fuse-ld=gold)
endif()
