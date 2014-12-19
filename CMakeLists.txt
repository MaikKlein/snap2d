cmake_minimum_required(VERSION 2.8.4)
project(snap2d)
set( CMAKE_EXPORT_COMPILE_COMMANDS 1 )
add_subdirectory(${CMAKE_SOURCE_DIR}/ext/glfw)
set(GLFW_BUILD_EXAMPLES OFF CACHE STRING "No Examples")

include_directories(
                    ${CMAKE_SOURCE_DIR}/ext/glm  
                    ${CMAKE_SOURCE_DIR}/ext/OglplusGen/oglplus
                    ${CMAKE_SOURCE_DIR}/ext/glfw/include
)
find_package(GLEW REQUIRED)
SET (CMAKE_CXX_COMPILER             "/usr/bin/clang++")
SET (CMAKE_CXX_FLAGS                "-std=c++1y -stdlib=libc++")
set(SOURCE_FILES src/main.cpp) 
add_executable(main  ${SOURCE_FILES})
target_link_libraries(main GLEW GL glfw ${GLFW_LIBRARIES})
