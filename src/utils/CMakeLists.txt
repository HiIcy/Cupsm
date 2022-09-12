
#add_library(service SHARED "")
add_library(utils_static STATIC "")

# FIXME: 需要优化，不然就重复代码编译了！
# 加入service的头文件引用,源文件构建target
target_include_directories(
        utils_static
        PRIVATE
        ${CMAKE_SOURCE_DIR}/src
        ${CMAKE_CURRENT_LIST_DIR}
        /home/wxk/pkg/xmlrpc/include)

target_sources(
        utils_static
        PRIVATE
        ${CMAKE_SOURCE_DIR}/src/service/UploadService.cpp
        ${CMAKE_CURRENT_LIST_DIR}/utils.cpp)

target_link_directories(
        utils_static
        PUBLIC
        /home/wxk/pkg/xmlrpc/lib)
       
target_link_libraries(utils_static  stdc++fs libxmlrpc_client++.a libxmlrpc_client.a libxmlrpc++.a libxmlrpc_util++.a libxmlrpc.a libxmlrpc_xmlparse.a libxmlrpc_xmltok.a libxmlrpc_util.a pthread curl libxmlrpc_packetsocket.a)


set_target_properties(utils_static PROPERTIES CLEAN_DIRECT_OUTPUT 1)
set(LIBRARY_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/lib)

