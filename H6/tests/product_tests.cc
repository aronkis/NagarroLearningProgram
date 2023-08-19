#include <gtest/gtest.h>
#include <string>

#include "../include/products_header.h"

TEST(ProductTester, IsEmptyTrue)
{
  Product product("", 0.0, 0);
  EXPECT_TRUE(product.IsEmpty());
}

TEST(ProductTester, IsEmptyFalse)
{
  Product product("Product", 12, 3);
  EXPECT_FALSE(product.IsEmpty());
}