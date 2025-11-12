cmake_minimum_required(VERSION 3.31)
project(flux-arduino)

set(CMAKE_CXX_STANDARD 17)
set(ION_LIB_DIR ${CMAKE_SOURCE_DIR}/libraries/ion-cpp)
set(FLUX_LIB_DIR ${CMAKE_SOURCE_DIR}/libraries/flux-cpp)
set(TRANSMISSION_LIB_DIR ${CMAKE_SOURCE_DIR}/libraries/transmission-cpp)
set(TRANSMISSION_ARDUINO_DIR ${CMAKE_SOURCE_DIR}/libraries/transmission-arduino)
set(AUDIO_ARDUINO_DIR ${CMAKE_SOURCE_DIR}/libraries/audio-arduino)
set(FLUX_LIB_SOURCE_DIR ${CMAKE_SOURCE_DIR}/libraries/flux-cpp/src)
set(FLUX_ARDUINO_DIR ${CMAKE_SOURCE_DIR}/libraries/flux-arduino)
set(FLUX_ARDUINO_SOURCE_DIR ${FLUX_ARDUINO_DIR}/src)
set(FLUX_ARDUINO_EXAMPLES_DIR ${FLUX_ARDUINO_DIR}/examples)
set(FLUX_ARDUINO_PROTOCOL_SERVER_DIR ${FLUX_ARDUINO_EXAMPLES_DIR}/flux-arduino-protocol-server)

# Define your sketch file
set(SKETCH_FILE ${FLUX_ARDUINO_PROTOCOL_SERVER_DIR}/flux-arduino-protocol-server.ino)

set(BOARD "rp2040:rp2040:adafruit_feather_rp2350_hstx")
set(PORT "/dev/cu.usbmodem1101")

set(OUTPUT_DIR ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/arduino/rp2350/flux-arduino)
file(GLOB_RECURSE FLUX_FILES ${FLUX_LIB_SOURCE_DIR}/*.cpp ${FLUX_ARDUINO_SOURCE_DIR}/*.cpp ${FLUX_ARDUINO_SOURCE_DIR}/*.ino)

add_executable(flux-arduino ${FLUX_FILES}
  ../flux-teensy/src/effects/gpio/GPIOEffects.cpp
  ../flux-teensy/src/effects/gpio/GPIOEffects.h
  ../flux-teensy/src/effects/serial/SerialEffects.cpp
  ../flux-teensy/src/effects/serial/SerialEffects.h
  src/effects/time/TimeEffects.cpp
  src/effects/time/TimeEffects.h
  src/effects/random/RandomEffects.cpp
  src/effects/random/RandomEffects.h)
add_dependencies(flux-arduino build_flux_arduino)
target_link_libraries(flux-arduino PRIVATE flux-cpp)

add_custom_target(build_flux_arduino ALL
        COMMAND arduino-cli compile
            --fqbn ${BOARD}
            --output-dir ${OUTPUT_DIR}
            --build-property "compiler.cpp.extra_flags=-std=c++17 -D_BSD_SOURCE -D_DEFAULT_SOURCE"
            --library ${ION_LIB_DIR}
            --library ${FLUX_LIB_DIR}
            --library ${FLUX_ARDUINO_DIR}
            --library ${TRANSMISSION_LIB_DIR}
            --library ${TRANSMISSION_ARDUINO_DIR}
            --library ${AUDIO_ARDUINO_DIR}
  ${SKETCH_FILE}
        WORKING_DIRECTORY ${FLUX_ARDUINO_SOURCE_DIR}
        COMMENT "Building flux-arduino with arduino-cli"
)

add_custom_target(upload_flux_arduino_protocol_server ALL
        COMMAND arduino-cli upload
        -p ${PORT}
        --fqbn ${BOARD}
        ${FLUX_ARDUINO_PROTOCOL_SERVER_DIR}
        COMMENT "Uploading flux-arduino-protocol-server with arduino-cli"
)
add_dependencies(upload_flux_arduino_protocol_server build_flux_arduino)

# Generate ctags for vim
set(TAGS_FILE ${FLUX_ARDUINO_SOURCE_DIR}/tags)
add_custom_target(
        GenerateArduinoTags
        COMMAND ctags -R -f ${TAGS_FILE} ${FLUX_LIB_SOURCE_DIR} ${FLUX_ARDUINO_SOURCE_DIR}
        WORKING_DIRECTORY ${FLUX_ARDUINO_SOURCE_DIR}
        COMMENT "Generating ctags"
)
add_dependencies(build_flux_arduino GenerateArduinoTags)