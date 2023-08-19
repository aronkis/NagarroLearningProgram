cmake_minimum_required(VERSION 3.2)

# GoogleTest requires at least C++14
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED true)

project(NagarroProjects VERSION 0.0.1)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/a0ced33ac6df214966bb90ba036e0a5666dca14e.zip
)

# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(
	main_tests
	tests/customer_tests.cc
	tests/product_tests.cc
	tests/printer_tests.cc
	tests/store_tests.cc
	tests/unique_pointer_tests.cc
	tests/shared_pointer_tests.cc
	src/product/product.cc
	src/product/alcoholic.cc
	src/product/book.cc
	src/product/toy.cc
	src/store.cc
	src/customer/customer.cc
	src/customer/affiliate_customer.cc
	src/customer/premium_customer.cc
	src/customer/underage_customer.cc
	src/printer/file_printer.cc
	src/printer/file_handler.cc
)

target_link_libraries(
	main_tests
	GTest::gtest_main
)

include(GoogleTest)
gtest_discover_tests(main_tests)