cmake_minimum_required(VERSION 3.21)
# specially: 115无法找到7.3 # xmlrpc貌似是用gcc7.3编译的导致这得找到7.3（必须放最前面不然可能找不到）
set(CMAKE_CXX_COMPILER "/usr/local/gcc7.3.0/bin/g++")
set(CMAKE_C_COMPILER "/usr/local/gcc7.3.0/bin/gcc")

project(Cupsm)

set(CMAKE_CXX_STANDARD 14)
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -lstdc++fs") # set C++ 11

# GLIBC新旧版本冲突
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -D_GLIBCXX_USE_CXX11_ABI=0 -fPIC -lstdc++fs")
#add_definitions("-O1")
#ADD_DEFINITIONS("-fPIC -lstdc++fs")

#set(CMAKE_CXX_FLAGS "-Wall -Werror")

include_directories(/home/wxk/pkg/xmlrpc/include)
link_directories(/home/wxk/pkg/xmlrpc/lib)
add_subdirectory(src)


add_executable(cupsm main.cpp)
target_link_libraries(cupsm constant service_static utils_static command)
#[[ #也可以?
target_link_libraries(cupsm libxmlrpc_client++.a libxmlrpc_client.a libxmlrpc++.a 
    libxmlrpc_util++.a libxmlrpc.a libxmlrpc_xmlparse.a libxmlrpc_xmltok.a 
    libxmlrpc_util.a pthread curl libxmlrpc_packetsocket.a constant service_static)
]]
