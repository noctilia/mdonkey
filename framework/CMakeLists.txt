get_filename_component(ProjectId ${CMAKE_CURRENT_LIST_DIR} NAME)
string(REPLACE " " "_" ProjectId ${ProjectId})
set(TARGET_NAME ${ProjectId})

aux_source_directory(${CMAKE_CURRENT_LIST_DIR} SOURCE_FILES)
add_library(${TARGET_NAME} ${SOURCE_FILES})

target_include_directories(${TARGET_NAME} PUBLIC ${CMAKE_CURRENT_LIST_DIR})
target_link_libraries(${TARGET_NAME} sfml-system sfml-window sfml-graphics sfml-network sfml-audio)

install(
    TARGETS ${TARGET_NAME}
    RUNTIME DESTINATION "."
    CONFIGURATIONS ${CMAKE_CONFIGURATION_TYPES}
)

install(
    DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/.
    DESTINATION ${CMAKE_INSTALL_PREFIX}/${BUILD_TYPE}
    FILES_MATCHING 
    PATTERN "*.png"
)



