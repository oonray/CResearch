cmake_minimum_required(VERSION 3.13)
project("basiccurl")

set(cmake_c_standard 99)
set(dir ${cmake_current_source_dir}/bin)
set(cmake_build_directory ${dir}/bin)
set(cmake_binary_dir  ${dir}/bin)
set(executable_output_path ${dir}/bin)

find_package(CURL REQUIRED)
include_directories(${CURL_INCLUDE_DIRS})

add_executable(basiccurl src/main.c)
target_link_libraries(basiccurl ${CURL_LIBRARIES})
