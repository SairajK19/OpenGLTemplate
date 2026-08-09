cmake_minimum_required(VERSION 3.10)
project(OpenGLProject)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(FILE_OFFSET_BITS 64)

find_package(PkgConfig REQUIRED)

add_compile_options(-Wall -ggdb -pg)

include_directories(OpenGLProject PUBLIC ${PROJECT_SOURCE_DIR}/include)
include_directories(OpenGLProject PUBLIC ${PROJECT_SOURCE_DIR}/core/include)
include_directories(OpenGLProject PUBLIC ${PROJECT_SOURCE_DIR}/lib/glad/include)
include_directories(OpenGLProject PUBLIC
                    ${PROJECT_SOURCE_DIR}/lib/glfw-3.4/include/GLFW)
include_directories(OpenGLProject PUBLIC
                    ${PROJECT_SOURCE_DIR}/lib/glm-1.0.3/glm/)
include_directories(OpenGLProject PUBLIC ${PROJECT_SOURCE_DIR}/lib/misc/)

add_subdirectory(./core)
add_subdirectory(./lib/glfw-3.4/)
add_subdirectory(./lib/glm-1.0.3)

add_executable(OpenGLProject main.cpp Application.cpp ${SOURCES}
                             ./lib/glad/src/glad.c core/include/Constants.h)
target_link_libraries(OpenGLProject PRIVATE glfw glm)

target_compile_definitions(OpenGLProject
                           PRIVATE PROJECT_DIR_ROOT="${PROJECT_SOURCE_DIR}")
