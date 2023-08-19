#include <gtest/gtest.h>
#include "../include/unique.hpp"

TEST(UniquePointerTester, ReleaseNullPtr)
{
  uniquePtr<int> value_pointer = uniquePtr(new int(10));
  int* value_pointer_released = value_pointer.release();

  EXPECT_EQ(value_pointer.get(), nullptr);
}

TEST(UniquePointerTester, ReleaseValue)
{
  uniquePtr<int> value_pointer = uniquePtr(new int(10));
  int* value_pointer_released = value_pointer.release();

  EXPECT_EQ(*value_pointer_released, 10);
}

TEST(UniquePointerTester, Reset)
{
  uniquePtr<int> value_pointer = uniquePtr(new int(10));
  value_pointer.reset();

  EXPECT_EQ(value_pointer.get(), nullptr);
}

TEST(UniquePointerTester, Swap)
{
  uniquePtr<int> value_pointer1 = uniquePtr(new int(10));
  uniquePtr<int> value_pointer2 = uniquePtr(new int(20));
 
  EXPECT_EQ(*(value_pointer1.get()), 10);
  EXPECT_EQ(*(value_pointer2.get()), 20);

  value_pointer1.swap(value_pointer2);

  EXPECT_NE(*(value_pointer1.get()), 10);
  EXPECT_NE(*(value_pointer2.get()), 20);
}
