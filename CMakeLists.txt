project(ezi)
cmake_minimum_required(VERSION 2.8)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake")
include(EnableCXX11)
include(BuildConfig)

find_package(Boost 1.49.0 REQUIRED COMPONENTS program_options)

set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR}/bin)
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR}/lib)

include_directories(
	src
	${Boost_INCLUDE_DIRS}
)

# add new directories here
add_subdirectory(src/io)
add_subdirectory(src/main)
