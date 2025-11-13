cmake_minimum_required(VERSION 3.31)
project(onda-arduino)

include(${CMAKE_HELPERS}/arduino-sdk.cmake)

set(CMAKE_CXX_STANDARD 17)
set(ONDA_CPP_SOURCE_DIR ${ONDA_CPP}/src)
set(ONDA_ARDUINO_SOURCE_DIR ${ONDA_ARDUINO}/src)
set(ONDA_ARDUINO_EXAMPLES_DIR ${ONDA_ARDUINO}/examples)
set(ONDA_ARDUINO_I2C_DIR ${ONDA_ARDUINO_EXAMPLES_DIR}/i2c)

# Define your sketch file
set(SKETCH_FILE ${ONDA_ARDUINO_I2C_DIR}/i2c.ino)

set(BOARD "esp32:esp32:adafruit_feather_esp32s3_nopsram")
set(PORT "/dev/cu.usbmodem1101")

set(OUTPUT_DIR ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/arduino/esp32/s3/onda-i2c)
file(GLOB_RECURSE ONDA_FILES ${ONDA_CPP_SOURCE_DIR}/*.cpp ${ONDA_ARDUINO_SOURCE_DIR}/*.cpp ${ONDA_ARDUINO_SOURCE_DIR}/*.ino)

add_executable(onda-arduino ${ONDA_FILES})
add_dependencies(onda-arduino build_onda_arduino_i2c)
target_link_libraries(onda-arduino PRIVATE onda)
target_link_arduino_sdk(onda-arduino esp32)

add_custom_target(build_onda_arduino_i2c ALL
        COMMAND arduino-cli compile
            --fqbn ${BOARD}
            --output-dir ${OUTPUT_DIR}
            --build-property "compiler.cpp.extra_flags=-std=c++17 -D_BSD_SOURCE -D_DEFAULT_SOURCE"
            --library ${ONDA_CPP}
            --library ${ONDA_ARDUINO}
  ${SKETCH_FILE}
        WORKING_DIRECTORY ${ONDA_ARDUINO}
        COMMENT "Building onda-arduino with arduino-cli"
)

add_custom_target(upload_onda_arduino_i2c ALL
        COMMAND arduino-cli upload
        -p ${PORT}
        --fqbn ${BOARD}
        ${ONDA_ARDUINO_I2C_DIR}
        COMMENT "Uploading onda-arduino-protocol-server with arduino-cli"
)
add_dependencies(upload_onda_arduino_i2c build_onda_arduino_i2c)