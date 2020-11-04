cmake_minimum_required(VERSION 3.6)

set(CMAKE_EXPORT_COMPILE_COMMANDS on)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(overload
        LANGUAGES CXX
        VERSION 1)

project(sockets
        LANGUAGES CXX
        VERSION 1)

project(stl
        LANGUAGES CXX
        VERSION 1)

project(transfors
        LANGUAGES CXX
        VERSION 1)

project(mapfilterreduce
        LANGUAGES CXX
        VERSION 1)


add_executable(overload basics/Overloading/src/main.cpp)
add_executable(sockets sockets/src/main.cpp)
add_executable(stl Tempaltes-STL/src/main.cpp)
add_executable(transforms Transforms/src/main.cpp)
add_executable(mapfilterreduce MapFilterReduce/src/main.cpp)

target_link_libraries(overload ${CONAN_LIBS})
target_link_libraries(sockets ${CONAN_LIBS})
target_link_libraries(stl ${CONAN_LIBS})
target_link_libraries(transforms ${CONAN_LIBS})
