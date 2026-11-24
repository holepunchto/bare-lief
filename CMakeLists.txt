cmake_minimum_required(VERSION 4.0)

find_package(cmake-bare REQUIRED PATHS node_modules/cmake-bare)
find_package(cmake-fetch REQUIRED PATHS node_modules/cmake-fetch)
find_package(cmake-napi REQUIRED PATHS node_modules/cmake-napi)

project(bare_lief C CXX)

fetch_package("github:holepunchto/libnapish#8cbfe78")
fetch_package("github:holepunchto/libjstl#7e31e67")

set(LIEF_USE_CCACHE OFF)

fetch_package(
  "github:lief-project/LIEF#1.0.0"
  PATCHES
    patches/001-macho-align-string-table.patch
    patches/002-elf-align-added-segment.patch
)

add_bare_module(bare_lief)

target_sources(
  ${bare_lief}
  PRIVATE
    binding.cc
    lib/handle.h
    lib/macho.h
    lib/elf.h
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

add_napi_module(bare_lief_napi)

target_sources(
  ${bare_lief_napi}
  PRIVATE
    binding.cc
    lib/handle.h
    lib/macho.h
    lib/elf.h
)

target_link_libraries(
  ${bare_lief_napi}
  PRIVATE
    jstl
    napish::static
  PRIVATE
    $<TARGET_OBJECTS:LIEF::LIEF>
  PUBLIC
    LIEF::LIEF
)

if(PROJECT_IS_TOP_LEVEL)
  add_subdirectory(test)
endif()
