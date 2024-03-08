cmake_minimum_required(VERSION 3.5.1)

project(adonkey VERSION 0.0.0 DESCRIPTION "adonkey")
set(TARGET_NAME adonkey)

option(BUILD_UNIT_TESTS "Build unit tests" ON)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/core ${CMAKE_CURRENT_SOURCE_DIR}/src/game)
file(GLOB SRC 
  src/*.cpp 
  src/assets/*.cpp 
  src/core/*.cpp 
  src/game/*.cpp 
  src/game/stages/*.cpp 
  src/hiscores/*.cpp
  src/hud/*.cpp 
  src/menu/*.cpp 
  src/title/*.cpp 
  src/stubs/*.cpp)
add_executable(${TARGET_NAME} WIN32 ${SRC} "src/wstub.cpp")

target_include_directories(${TARGET_NAME} PUBLIC src)
target_include_directories(${TARGET_NAME} PUBLIC 
  ${SDL2_INCLUDE_DIR} 
  ${SDL2_IMAGE_INCLUDE_DIR} 
  ${SDL2_NET_INCLUDE_DIR} 
  ${SDL2_MIXER_INCLUDE_DIR} 
  ${SDL2_TTF_INCLUDE_DIR}
  )

target_link_libraries(${TARGET_NAME} sfml-system sfml-window sfml-graphics sfml-network sfml-audio)

# install the target
#install(TARGETS ${TARGET_NAME} DESTINATION ".")

set (CMAKE_INSTALL_SYSTEM_RUNTIME_LIBS ${COPYDLLS})
set (CMAKE_INSTALL_SYSTEM_RUNTIME_LIBS_SKIP TRUE)
include(InstallRequiredSystemLibraries)

if( CMAKE_INSTALL_SYSTEM_RUNTIME_LIBS )
  install(PROGRAMS ${CMAKE_INSTALL_SYSTEM_RUNTIME_LIBS} DESTINATION ${TARGET_NAME} COMPONENT System)
endif( CMAKE_INSTALL_SYSTEM_RUNTIME_LIBS )

install(
    TARGETS ${TARGET_NAME}
    RUNTIME DESTINATION ${TARGET_NAME}
    CONFIGURATIONS ${CMAKE_CONFIGURATION_TYPES}
)

install(
    DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/assets/
    DESTINATION ${CMAKE_INSTALL_PREFIX}/${BUILD_TYPE}/${TARGET_NAME}/assets/
    FILES_MATCHING 
    PATTERN "*.*"
)