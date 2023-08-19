CMAKE_MINIMUM_REQUIRED (VERSION 3.2)
project(ClientServer)

find_package(Boost REQUIRED COMPONENTS serialization)
include_directories(${Boost_INCLUDE_DIRS})

add_executable(client_main client_main.cc
              src/client.cc)

add_executable(server_main server_main.cc
              src/server.cc)

target_link_libraries(client_main ${Boost_LIBRARIES})
target_link_libraries(server_main ${Boost_LIBRARIES})
