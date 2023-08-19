CMAKE_MINIMUM_REQUIRED (VERSION 3.2)
project(GeneralStore)

add_executable(main main.cc
              src/Client/client.cc
              src/Client/premium_client.cc
              src/Client/regular_client.cc
              src/Client/under_age_client.cc
              src/store.cc
              src/printer.cc)
target_include_directories(main PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/include)
