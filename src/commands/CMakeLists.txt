
#add_library(service SHARED "")
add_library(command STATIC "")

message(STATUS "commandpath=${CMAKE_SOURCE_DIR}/src")

target_include_directories(
        command
        PUBLIC
        ${CMAKE_SOURCE_DIR}/src/utils
        ${CMAKE_CURRENT_LIST_DIR})

target_sources(
        command
        PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}/../utils/utils.cpp
        ${CMAKE_CURRENT_LIST_DIR}/command.cpp)

#set_target_properties(service PROPERTIES OUTPUT_NAME "service")
# 动态库和静态库同时存在
#set_target_properties(service PROPERTIES CLEAN_DIRECT_OUTPUT 1)
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

