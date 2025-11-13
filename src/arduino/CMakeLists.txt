cmake_minimum_required(VERSION 3.31)
project(flux-arduino)

include(${CMAKE_HELPERS}/arduino-sdk.cmake)

set(CMAKE_CXX_STANDARD 17)
set(FLUX_CPP_SOURCE_DIR ${FLUX_CPP}/src)
set(FLUX_ARDUINO_SOURCE_DIR ${FLUX_ARDUINO}/src)
set(FLUX_ARDUINO_EXAMPLES_DIR ${FLUX_ARDUINO}/examples)
set(FLUX_ARDUINO_I2C_DIR ${FLUX_ARDUINO_EXAMPLES_DIR}/i2c)

# Define your sketch file
set(SKETCH_FILE ${FLUX_ARDUINO_I2C_DIR}/i2c.ino)

set(BOARD "esp32:esp32:adafruit_feather_esp32s3_nopsram")
set(PORT "/dev/cu.usbmodem1101")

set(OUTPUT_DIR ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/arduino/esp32/s3/flux-i2c)
file(GLOB_RECURSE FLUX_FILES ${FLUX_CPP_SOURCE_DIR}/*.cpp ${FLUX_ARDUINO_SOURCE_DIR}/*.cpp ${FLUX_ARDUINO_SOURCE_DIR}/*.ino)

add_executable(flux-arduino ${FLUX_FILES})
add_dependencies(flux-arduino build_flux_arduino_i2c)
target_link_libraries(flux-arduino PRIVATE flux-cpp)
target_link_arduino_sdk(flux-arduino esp32)

add_custom_target(build_flux_arduino_i2c ALL
        COMMAND arduino-cli compile
            --fqbn ${BOARD}
            --output-dir ${OUTPUT_DIR}
            --build-property "compiler.cpp.extra_flags=-std=c++17 -D_BSD_SOURCE -D_DEFAULT_SOURCE"
            --library ${FLUX_CPP}
            --library ${FLUX_ARDUINO}
  ${SKETCH_FILE}
        WORKING_DIRECTORY ${FLUX_ARDUINO}
        COMMENT "Building flux-arduino with arduino-cli"
)

add_custom_target(upload_flux_arduino_i2c ALL
        COMMAND arduino-cli upload
        -p ${PORT}
        --fqbn ${BOARD}
        ${FLUX_ARDUINO_I2C_DIR}
        COMMENT "Uploading flux-arduino-protocol-server with arduino-cli"
)
add_dependencies(upload_flux_arduino_i2c build_flux_arduino_i2c)