cmake_minimum_required(VERSION 3.14)

add_library(${PROJECT_NAME})
target_sources(
    ${PROJECT_NAME}
    PRIVATE
    domino/domino.cpp
    domino/domino.h
)
target_include_directories(${PROJECT_NAME} PUBLIC .)
