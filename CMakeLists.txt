cmake_minimum_required(VERSION 3.10)
project(ascii_art)

# Use C++17
set(CMAKE_CXX_STANDARD 17)

# Find OpenCV
find_package(OpenCV REQUIRED)

# Include headers (now in src/)
include_directories(
    src
    ${OpenCV_INCLUDE_DIRS}
)

# Add executable and source files
add_executable(ascii_art
    src/main.c++
    src/ascii_modes.c++
    src/image_utils.c++
)

# Link OpenCV libraries
target_link_libraries(ascii_art ${OpenCV_LIBS})

# Optional: copy examples folder to build output after build
add_custom_command(TARGET ascii_art POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/examples $<TARGET_FILE_DIR:ascii_art>/examples
)