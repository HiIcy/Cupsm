
add_library(constant "")

target_include_directories(
        constant
        PUBLIC
        ${CMAKE_CURRENT_LIST_DIR})

target_sources(
        constant
        PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/constants.cpp)



set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)
