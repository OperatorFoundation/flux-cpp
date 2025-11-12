cmake_minimum_required(VERSION 3.31)
project(flux-cpp)
set(CMAKE_CXX_STANDARD 17)
enable_testing()

set(FLUX_LIB_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(FLUX_LIB_SOURCE_DIR ${FLUX_LIB_DIR}/src)

file(GLOB_RECURSE FLUX_FILES ${FLUX_LIB_SOURCE_DIR}/*.cpp)
message(STATUS "FLUX source dir: ${FLUX_LIB_SOURCE_DIR}")
message(STATUS "FLUX_FILES found: ${FLUX_FILES}")

add_library(flux-cpp STATIC ${FLUX_FILES})

target_include_directories(flux-cpp PUBLIC
  ${FLUX_LIB_SOURCE_DIR}
)

if(ENABLE_COVERAGE AND (CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CX_COMPILER_ID MATCHES "Clang"))
  target_compile_options(flux-cpp PRIVATE --coverage -O0 -g)
  target_link_options(flux-cpp PRIVATE --coverage)
endif()