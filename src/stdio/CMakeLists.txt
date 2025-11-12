cmake_minimum_required(VERSION 3.31)
project(flux-stdio)

set(CMAKE_CXX_STANDARD 17)

set(FLUX_STDIO_DIR ${CMAKE_SOURCE_DIR}/flux-stdio)
set(FLUX_LIB_DIR ${CMAKE_SOURCE_DIR}/libraries/flux-cpp)
set(OUTPUT_DIR ${CMAKE_BINARY_DIR}/bin)

add_executable(flux-stdio
  FluxMain.cpp
  IostreamConnection.cpp
  IostreamStorageConnection.cpp
  main.cpp
)
target_link_libraries(flux-stdio flux-cpp-lib)

# Generate ctags for vim
set(TAGS_FILE ${FLUX_STDIO_DIR}/tags)
add_custom_target(
        GenerateStdfluxgs
        COMMAND ctags -R -f ${TAGS_FILE} ${FLUX_STDIO_DIR} ${FLUX_LIB_DIR}
        WORKING_DIRECTORY ${FLUX_DIR}
        COMMENT "Generating ctags"
)
add_dependencies(${PROJECT_NAME} GenerateStdfluxgs)
