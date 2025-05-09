CMAKE_MINIMUM_REQUIRED(VERSION 3.5)
project(Logger)
set(CMAKE_CXX_STANDARD 20)
include_directories(include)

file(GLOB SOURCES "src/*.cpp")
file(GLOB_RECURSE HEADERS "include/*.h include/*.hpp")

add_executable(${PROJECT_NAME} ${SOURCES})
