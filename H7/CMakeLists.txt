CMAKE_MINIMUM_REQUIRED (VERSION 3.2)
project(Restaurant)

add_executable(main main.cc
              src/client.cc
              src/restaurant.cc
              src/dish.cc)
target_include_directories(main PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)