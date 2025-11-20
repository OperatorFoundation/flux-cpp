add_library(onda-macos src/onda-macos.h
  src/stdio_logger.cpp
  src/stdio_logger.h
  src/onda-macos.h)

target_link_libraries(onda-macos PUBLIC onda)

target_include_directories(onda-macos PRIVATE src)

if(APPLE)
    target_link_libraries(onda-macos PUBLIC
        "-framework CoreFoundation"
        "-framework IOKit"
    )
endif()

target_compile_features(onda-macos PUBLIC cxx_std_17)