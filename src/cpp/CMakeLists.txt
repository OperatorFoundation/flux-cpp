cmake_minimum_required(VERSION 3.31)
project(onda)
set(CMAKE_CXX_STANDARD 17)
enable_testing()

set(ONDA_LIB_DIR ${CMAKE_CURRENT_SOURCE_DIR})
set(ONDA_LIB_SOURCE_DIR ${ONDA_LIB_DIR}/src)

file(GLOB_RECURSE ONDA_FILES ${ONDA_LIB_SOURCE_DIR}/*.cpp)
message(STATUS "ONDA source dir: ${ONDA_LIB_SOURCE_DIR}")
message(STATUS "ONDA_FILES found: ${ONDA_FILES}")

add_library(onda STATIC ${ONDA_FILES})

target_include_directories(onda PUBLIC
  ${ONDA_LIB_SOURCE_DIR}
)

if(ENABLE_COVERAGE AND (CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CX_COMPILER_ID MATCHES "Clang"))
  target_compile_options(onda PRIVATE --coverage -O0 -g)
  target_link_options(onda PRIVATE --coverage)
endif()