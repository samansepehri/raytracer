cmake_minimum_required(VERSION 3.15)

project(testas)
add_executable(testas src/main.cpp)
find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)
include_directories( ${OPENGL_INCLUDE_DIRS}  ${GLUT_INCLUDE_DIRS} )

target_link_libraries(testas ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} )