CMAKE_MINIMUM_REQUIRED(VERSION 3.5)
project(Logger)
set(CMAKE_CXX_STANDARD 20)
set(LIB_NAME CustomLogger)
include_directories(include)

file(GLOB SOURCES "src/*.cpp")
file(GLOB_RECURSE HEADERS "include/*.h include/*.hpp")

add_library(${LIB_NAME} SHARED ${SOURCES})
add_executable(${PROJECT_NAME} ${SOURCES})
target_include_directories(${LIB_NAME} PUBLIC 
$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>)


install(TARGETS ${LIB_NAME} EXPORT LoggerConfig
    LIBRARY DESTINATION /usr/local/lib
    ARCHIVE DESTINATION /usr/local/lib
)
install(DIRECTORY include/ DESTINATION /usr/local/include)
install(EXPORT LoggerConfig DESTINATION /usr/local/lib/cmake/LoggerConfig)
