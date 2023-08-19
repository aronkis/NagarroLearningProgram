#include <gtest/gtest.h>
#include "../include/shared.hpp"


TEST(SharedPointerTester, CopyWithEqualOperator)
{
  SharedPtr<int> value_pointer1 = SharedPtr(new int(10));
  SharedPtr<int> value_pointer2 = value_pointer1;

  EXPECT_EQ(*(value_pointer1.get()), *(value_pointer2.get()));
  EXPECT_EQ(value_pointer1.use_count(), 2);
}

TEST(SharedPointerTester, CopyWithFunction)
{
  SharedPtr<int> value_pointer1 = SharedPtr(new int(10));
  SharedPtr<int> value_pointer2(value_pointer1);

  EXPECT_EQ(*(value_pointer1.get()), *(value_pointer2.get()));
  EXPECT_EQ(value_pointer1.use_count(), 2);
}

TEST(SharedPointerTester, Reset)
{
  SharedPtr<int> value_pointer = SharedPtr(new int(10));
  value_pointer.reset();

  EXPECT_EQ(value_pointer.get(), nullptr);
}

TEST(SharedPointerTester, Swap)
{
  SharedPtr<int> value_pointer1 = SharedPtr(new int(10));
  SharedPtr<int> value_pointer2 = SharedPtr(new int(20));
 
  EXPECT_EQ(*(value_pointer1.get()), 10);
  EXPECT_EQ(*(value_pointer2.get()), 20);

  value_pointer1.swap(value_pointer2);

  EXPECT_NE(*(value_pointer1.get()), 10);
  EXPECT_NE(*(value_pointer2.get()), 20);
}

TEST(SharedPointerTester, UniqueTrue)
{
  SharedPtr<int> value_pointer1 = SharedPtr(new int(10));

  EXPECT_TRUE(value_pointer1.unique());
}

TEST(SharedPointerTester, UniqueFalse)
{
  SharedPtr<int> value_pointer1 = SharedPtr(new int(10));
  SharedPtr<int> value_pointer2 = value_pointer1;

  EXPECT_FALSE(value_pointer1.unique());
}

TEST(SharedPointerTester, Owner_Before)
{
  SharedPtr<int> value_pointer1 = SharedPtr(new int(10));
  SharedPtr<int> value_pointer2;

  EXPECT_TRUE(value_pointer1.owner_before(value_pointer2));
}