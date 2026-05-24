cmake_minimum_required(VERSION 3.15)
project(shtop)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

set(SRC_DIR ${PROJECT_SOURCE_DIR}/src)
set(INC_DIR ${PROJECT_SOURCE_DIR}/include)

add_executable(${PROJECT_NAME}
  ${SRC_DIR}/proc_parse.cpp
  ${SRC_DIR}/main.cpp
)

target_include_directories(${PROJECT_NAME} PRIVATE ${INC_DIR})
