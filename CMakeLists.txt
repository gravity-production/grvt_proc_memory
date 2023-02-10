cmake_minimum_required(VERSION 3.24)
project(proc_memory)

set(CMAKE_CXX_STANDARD 17)

set(Directories
        )

Set(Sources
        proc_memory.hpp proc_memory.cpp)

add_library(proc_memory STATIC ${Sources})
target_include_directories(proc_memory PRIVATE ${Directories})
