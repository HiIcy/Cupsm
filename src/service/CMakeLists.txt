
#add_library(service SHARED "")
add_library(service_static STATIC "")
#[[
target_include_directories(
        service
        PUBLIC
        ${CMAKE_CURRENT_LIST_DIR})
target_sources(
        service
        PUBLIC
        ${CMAKE_CURRENT_LIST_DIR}/../constants/constants.cpp
        ${CMAKE_CURRENT_LIST_DIR}/UploadService.cpp)
]]

target_include_directories(
        service_static
        PRIVATE
        ${CMAKE_CURRENT_LIST_DIR}
        /home/wxk/pkg/xmlrpc/include)

target_sources(
       service_static
       PRIVATE
       ${CMAKE_CURRENT_LIST_DIR}/../constants/constants.cpp
       ${CMAKE_CURRENT_LIST_DIR}/UploadService.cpp)

target_link_directories(
        service_static
        PUBLIC
        /home/wxk/pkg/xmlrpc/lib)
       
#target_link_libraries(service libxmlrpc_client++.a libxmlrpc_client.a libxmlrpc++.a libxmlrpc_util++.a libxmlrpc.a libxmlrpc_xmlparse.a libxmlrpc_xmltok.a libxmlrpc_util.a pthread curl libxmlrpc_packetsocket.a)
target_link_libraries(service_static libxmlrpc_client++.a libxmlrpc_client.a libxmlrpc++.a libxmlrpc_util++.a libxmlrpc.a libxmlrpc_xmlparse.a libxmlrpc_xmltok.a libxmlrpc_util.a pthread curl libxmlrpc_packetsocket.a)

#set_target_properties(service PROPERTIES OUTPUT_NAME "service")
# 动态库和静态库同时存在
#set_target_properties(service PROPERTIES CLEAN_DIRECT_OUTPUT 1)
set_target_properties(service_static PROPERTIES CLEAN_DIRECT_OUTPUT 1)
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

