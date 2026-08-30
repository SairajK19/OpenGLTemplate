cmake_minimum_required(VERSION 3.10)
project(OpenGLTemplate)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(FILE_OFFSET_BITS 64)

find_package(PkgConfig REQUIRED)

add_compile_options(-Wall -ggdb -pg)

include_directories(OpenGLTemplate PUBLIC ${PROJECT_SOURCE_DIR}/include)
include_directories(OpenGLTemplate PUBLIC ${PROJECT_SOURCE_DIR}/core/include)
include_directories(OpenGLTemplate PUBLIC ${PROJECT_SOURCE_DIR}/lib/glad/include)
include_directories(OpenGLTemplate PUBLIC
                    ${PROJECT_SOURCE_DIR}/lib/glfw-3.4/include/GLFW)
include_directories(OpenGLTemplate PUBLIC ${PROJECT_SOURCE_DIR}/lib/glm-1.0.3/glm/)
include_directories(OpenGLTemplate PUBLIC ${PROJECT_SOURCE_DIR}/lib/misc/)
include_directories(OpenGLTemplate PUBLIC
                    ${PROJECT_SOURCE_DIR}/lib/json-3.12.0/include)

add_subdirectory(./core)
add_subdirectory(./lib/glfw-3.4/)
add_subdirectory(./lib/glm-1.0.3)
add_subdirectory(./lib/json-3.12.0)

add_executable(
  OpenGLTemplate main.cpp Application.cpp ${SOURCES} ./lib/glad/src/glad.c)
target_link_libraries(OpenGLTemplate PRIVATE glfw glm nlohmann_json)

target_compile_definitions(OpenGLTemplate
                           PRIVATE PROJECT_DIR_ROOT="${PROJECT_SOURCE_DIR}")
