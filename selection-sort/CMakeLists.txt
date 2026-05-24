cmake_minimum_required(VERSION 4.1.1)
project(SelectionSort)



add_executable(${PROJECT_NAME} src/main.cpp )
target_link_libraries(${PROJECT_NAME})

target_include_directories(${PROJECT_NAME} PRIVATE
    ${CMAKE_SOURCE_DIR}/include
)