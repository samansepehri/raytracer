cmake_minimum_required(VERSION 3.15)

project(raytracer)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

include_directories( ${OPENGL_INCLUDE_DIRS}  ${GLUT_INCLUDE_DIRS} ext )

set(TinyXML ext/tinyxml2/tinyxml2.cpp ext/tinyxml2/tinyxml2.h )
add_executable(raytracer src/main.cpp ${TinyXML})

target_link_libraries(raytracer ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} )