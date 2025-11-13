cmake_minimum_required(VERSION 3.31)
project(onda-lib-tests)

set(CMAKE_CXX_STANDARD 17)
enable_testing()

set(CTEST_PROJECT_NAME onda)
set(CTEST_NIGHTLY_START_TIME 01:00:00 UTC)
set(CTEST_SUBMIT_URL https://my.cdash.org/submit.php?project=onda)
set(CTEST_DROP_SITE_CDASH TRUE)

include(FetchContent)
FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG v3.8.0
)

FetchContent_MakeAvailable(Catch2)

set(ONDA_LIB_DIR ${CMAKE_SOURCE_DIR}/libraries/onda)
set(ONDA_LIB_SOURCE_DIR ${ONDA_LIB_DIR}/src)
set(ION_LIB_DIR ${CMAKE_SOURCE_DIR}/libraries/ion-cpp)
set(ION_LIB_SOURCE_DIR ${ION_LIB_DIR}/src)
set(TRANSMISSION_LIB_DIR ${CMAKE_SOURCE_DIR}/libraries/transmission-cpp)
set(TRANSMISSION_LIB_SOURCE_DIR ${TRANSMISSION_LIB_DIR}/src)
set(BIGNUMBER_LIB_DIR ${CMAKE_SOURCE_DIR}/libraries/bignumber-cpp)
set(BIGNUMBER_LIB_SOURCE_DIR ${BIGNUMBER_LIB_DIR}/src)

set(OUTPUT_DIR ${CMAKE_BINARY_DIR}/bin)

add_executable(onda-tests main.cpp)
target_include_directories(onda-tests PRIVATE
  ${ONDA_LIB_SOURCE_DIR}
)

target_link_libraries(onda-tests PRIVATE onda Catch2::Catch2WithMain)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  option(ENABLE_COVERAGE "Enable coverage reporting" ON)

  target_compile_options(onda-tests PRIVATE --coverage -O0 -g)
  target_link_options(onda-tests PRIVATE --coverage)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -g")

  find_program(GCOV_PATH gcov)
  find_program(LCOV_PATH lcov)
  find_program(GENHTML_PATH genhtml)

  if(LCOV_PATH AND GCOV_PATH AND GENHTML_PATH)
    add_custom_target(onda-coverage
      COMMAND ${LCOV_PATH} --directory . --zerocounters
      COMMAND tests
      COMMAND ${LCOV_PATH} --directory . --capture --output-file coverage.info
      COMMAND ${LCOV_PATH} --extract coverage.info
      '${CMAKE_SOURCE_DIR}/libraries/onda/*'
      --output-file coverage.filtered.info
      COMMAND ${GENHTML_PATH} coverage.filtered.info --output-directory coverage_html
      WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
      COMMENT "Generating coverage report"
    )
  else()
    # Fallback to gcov directly
    add_custom_target(onda-coverage
      COMMAND ${CMAKE_COMMAND} -E remove_directory coverage
      COMMAND ${CMAKE_COMMAND} -E make_directory coverage
      COMMAND tests
      COMMAND ${CMAKE_COMMAND} -E chdir coverage ${GCOV_PATH} -abcfu ${CMAKE_SOURCE_DIR}/src/*.cpp
      WORKING_DIRECTORY ${CMAKE_BINARY_DIR}
      COMMENT "Running gcov"
    )
  endif()
endif()