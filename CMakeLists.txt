cmake_minimum_required(VERSION 3.21)
project(Cupsm)

set(CMAKE_CXX_STANDARD 14)
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14") # set C++ 11


# specially: 115无法找到7.3
#set(CMAKE_CXX_COMPILER /usr/local/gcc7.3.0/bin/g++)
#set(CMAKE_C_COMPILER /usr/local/gcc7.3.0/bin/gcc)


#add_definitions("-O1")
#add_definitions("-fPIC")
ADD_DEFINITIONS("-fPIC")

#set(CMAKE_CXX_FLAGS "-Wall -Werror")

include_directories(/home/wxk/pkg/xmlrpc/include)
link_directories(/home/wxk/pkg/xmlrpc/lib)
add_subdirectory(src)


add_executable(cupsm main.cpp)
target_link_libraries(cupsm constant service_static)
#target_link_libraries(cupsm libxmlrpc_client++.a libxmlrpc_client.a libxmlrpc++.a libxmlrpc_util++.a libxmlrpc.a libxmlrpc_xmlparse.a libxmlrpc_xmltok.a libxmlrpc_util.a pthread curl libxmlrpc_packetsocket.a constant service)

