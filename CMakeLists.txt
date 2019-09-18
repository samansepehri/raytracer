cmake_minimum_required(VERSION 3.15)
set (CMAKE_CXX_STANDARD 11)

project(raytracer)

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

include_directories( ${OPENGL_INCLUDE_DIRS}  ${GLUT_INCLUDE_DIRS} ext )

set(TINYXML ext/tinyxml/tinyxml.cpp ext/tinyxml/tinyxml.h
            ext/tinyxml/tinyxmlerror.cpp
            ext/tinyxml/tinystr.cpp ext/tinyxml/tinystr.h
            ext/tinyxml/tinyxmlparser.cpp )
set(CYCODE  ext/cyCodeBase/cyVector.h
            ext/cyCodeBase/cyMatrix.h
            ext/cyCodeBase/cyColor.h )
set(LODEPNG ext/lodepng/lodepng.cpp ext/lodepng/lodepng.h )

add_executable(raytracer src/main.cpp
                ${TINYXML} ${CYCODE} ${LODEPNG})
                #src/viewport.cpp
                #src/xmlload.cpp)

add_compile_definitions(USE_GLUT)

target_link_libraries(raytracer ${OPENGL_LIBRARIES} ${GLUT_LIBRARY} )