cmake_minimum_required(VERSION 3.10)

project(Seri)

# Include OpenFst headers (assuming default installation path)
include_directories(/usr/local/include)

# Add the source files
set(SOURCE_FILES main.cpp src/io.cpp src/io.h)

# Create the executable
add_executable(Seri ${SOURCE_FILES})

# Link the OpenFst library (assuming default installation path)
target_link_libraries(Seri /usr/local/lib/libfst.so)