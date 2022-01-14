cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

project(EMBEDDED_EXAMEN_C)

add_executable(${PROJECT_NAME} main.c)

TARGET_LINK_LIBRARIES( ${PROJECT_NAME}
pthread
)