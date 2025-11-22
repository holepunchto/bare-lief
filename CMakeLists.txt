cmake_minimum_required(VERSION 4.0)

find_package(cmake-bare REQUIRED PATHS node_modules/cmake-bare)
find_package(cmake-fetch REQUIRED PATHS node_modules/cmake-fetch)

project(bare_lief C CXX)

fetch_package("github:holepunchto/libjstl#b785ee1")

set(LIEF_USE_CCACHE OFF)

fetch_package("github:lief-project/LIEF#0.17.1")

add_bare_module(bare_lief)

target_sources(
  ${bare_lief}
  PRIVATE
    binding.cc
)

target_link_libraries(
  ${bare_lief}
  PRIVATE
    jstl
  PRIVATE
    $<TARGET_OBJECTS:LIEF::LIEF>
  PUBLIC
    LIEF::LIEF
)

if(PROJECT_IS_TOP_LEVEL)
  add_subdirectory(test)
endif()
