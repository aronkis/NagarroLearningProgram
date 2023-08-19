CMAKE_MINIMUM_REQUIRED (VERSION 3.2)
project (Pointers)
add_executable(main main.cc)
target_include_directories(main PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)