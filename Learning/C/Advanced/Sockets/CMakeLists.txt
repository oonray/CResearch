cmake_minimum_required(version 3.13)
project("reverse_tcp_server")
project("reverse_tcp_client")
set(cmake_c_standard 99)

set(dir ${cmake_current_source_dir}/bin)
set(cmake_build_directory ${dir})
set(cmake_binary_dir  ${dir})
set(executable_output_path ${dir})

find_package(curses required)
include_directories(${curses_include_dir})

add_executable(reverse_tcp_server src/server.c src/menu.h src/curdbg.h src/colors.h src/win.h)
add_executable(reverse_tcp_client src/client.c)

target_link_libraries(reverse_tcp_server ${curses_libraries})
target_link_libraries(reverse_tcp_client ${curses_libraries})

