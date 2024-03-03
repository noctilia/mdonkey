cmake_minimum_required(VERSION 3.11)
project(snowman VERSION 0.0.1 DESCRIPTION "wdonkey")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
endif()

# Find SFML
set(SFML_STATIC_LIBRARIES TRUE)
find_package(SFML 2.5 COMPONENTS graphics audio REQUIRED)


# Add SDL2 CMake modules
#list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/sdl2)

# Set output path
#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# Find SDL2
#find_package(SDL2 REQUIRED)
#find_package(SDL2_image REQUIRED)
#find_package(SDL2_net REQUIRED)
#find_package(SDL2_mixer REQUIRED)
#find_package(SDL2_ttf REQUIRED)

# Set output path
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# file ( GLOB_RECURSE PROJECTS ${CMAKE_SOURCE_DIR}/*/CMakeLists.txt )
# collect only first level projects
file (GLOB PROJECTS ${CMAKE_SOURCE_DIR}/*/CMakeLists.txt)
foreach (PRJ ${PROJECTS})
  get_filename_component(PRJ_PATH ${PRJ} DIRECTORY)
  message(STATUS " adding project " ${PRJ_PATH})
  add_subdirectory(${PRJ_PATH})
endforeach()

file (GLOB PROJECTS
  ${CMAKE_SOURCE_DIR}/tools/*/CMakeLists.txt
  ${CMAKE_SOURCE_DIR}/playground/*/CMakeLists.txt)
foreach (PRJ ${PROJECTS})
  get_filename_component(PRJ_PATH ${PRJ} DIRECTORY)
  message(STATUS " adding project " ${PRJ_PATH})
  add_subdirectory(${PRJ_PATH})
endforeach()