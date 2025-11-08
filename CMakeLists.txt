cmake_minimum_required(VERSION 4.1.1)
project(hashing-demo)



add_executable(${PROJECT_NAME} src/main.cc )
target_link_libraries(${PROJECT_NAME})

target_include_directories(${PROJECT_NAME} PRIVATE)