#include <gtest/gtest.h>
#include <string>
#include <unordered_map>

#include "../include/printers_header.h"
#include "../include/products_header.h"
#include "../include/customers_header.h"
#include "../include/unique.hpp"

FileHandler Logger::log_("data/log.txt");

TEST(CustomerTester, AddToCart)
{
  uniquePtr<Product> prod_01(new Toy("Teddy", "Sc. Toy", 24, 6, 3));
  uniquePtr<Product> prod_02(new Alcoholic("Vodka", 20.99, 21, 750.0, 1));

  std::unordered_map<std::string, uniquePtr<Product>> expected_items;
  expected_items.insert(std::make_pair("1", (new Toy("Teddy", "Sc. Toy", 24, 6, 3))));
  expected_items.insert(std::make_pair("2", (new Alcoholic("Vodka", 20.99, 21, 750.0, 1))));

  PremiumCustomer premium_customer("PremiumCustomer", "somewhere");
  premium_customer.AddToCart("1", prod_01);
  premium_customer.AddToCart("2", prod_02);

  EXPECT_STREQ(expected_items.at("1").get()->GetName().c_str(), premium_customer.GetShoppingCart().at("1").get()->GetName().c_str());
  EXPECT_DOUBLE_EQ(expected_items.at("1").get()->GetPrice(), premium_customer.GetShoppingCart().at("1").get()->GetPrice());
  EXPECT_EQ(expected_items.at("1").get()->GetQuantity(), premium_customer.GetShoppingCart().at("1").get()->GetQuantity());
 
  EXPECT_STREQ(expected_items.at("2").get()->GetName().c_str(), premium_customer.GetShoppingCart().at("2").get()->GetName().c_str());
  EXPECT_DOUBLE_EQ(expected_items.at("2").get()->GetPrice(), premium_customer.GetShoppingCart().at("2").get()->GetPrice());
  EXPECT_EQ(expected_items.at("2").get()->GetQuantity(), premium_customer.GetShoppingCart().at("2").get()->GetQuantity());
}

TEST(CustomerTester, ClearShoppingCart)
{
  uniquePtr<Product> prod_01(new Toy("Teddy", "Sc. Toy", 24, 6, 3));
  uniquePtr<Product> prod_02(new Alcoholic("Vodka", 20.99, 21, 750.0, 1));
  PremiumCustomer premium_customer("PremiumCustomer", "somewhere");
  
  premium_customer.AddToCart("1", prod_01);
  premium_customer.AddToCart("2", prod_02);

  premium_customer.ClearShoppingCart();

  EXPECT_EQ(premium_customer.GetShoppingCart().size(), 0);
}

TEST(CustomerTester, RemoveProductAll)
{
  uniquePtr<Product> prod_01(new Toy("Teddy", "Sc. Toy", 24, 6, 3));
  uniquePtr<Product> prod_02(new Toy("MatchBox", "Sc. Toy", 50, 3, 3));
  uniquePtr<Product> prod_03(new Alcoholic("Vodka", 20.99, 21, 750.0, 1));
  PremiumCustomer premium_customer("PremiumCustomer", "somewhere");

  premium_customer.AddToCart("1", prod_01);
  premium_customer.AddToCart("2", prod_02);
  premium_customer.AddToCart("3", prod_03);

  premium_customer.RemoveProduct("2", 3);

  std::string not_expected_output = "MatchBox";

  for (auto& [first, second]: premium_customer.GetShoppingCart())
  {
    EXPECT_STRNE(second.get()->GetName().c_str(), not_expected_output.c_str());
  }

}

TEST(CustomerTester, RemoveProductPartially)
{
  uniquePtr<Product> prod_01(new Toy("Teddy", "Sc. Toy", 24, 6, 3));
  PremiumCustomer premium_customer("PremiumCustomer", "somewhere");

  premium_customer.AddToCart("1", prod_01);

  premium_customer.RemoveProduct("1", 2);

  EXPECT_EQ(premium_customer.GetShoppingCart().at("1").get()->GetQuantity(), 1);
}

TEST(CustomerTester, IsEmptyTrue)
{
  PremiumCustomer premium_customer("", "");
  EXPECT_TRUE(premium_customer.IsEmpty());
}

TEST(CustomerTester, IsEmptyFalse)
{
  PremiumCustomer premium_customer1("PremiumCustomer", "somewhere");
  EXPECT_FALSE(premium_customer1.IsEmpty());
}

TEST(CustomerTester, FindProductTrue)
{
  uniquePtr<Product> prod_01(new Toy("Teddy", "Sc. Toy", 24, 6, 3));
  uniquePtr<Product> prod_02(new Toy("MatchBox", "Sc. Toy", 50, 3, 3));
  uniquePtr<Product> prod_03(new Alcoholic("Vodka", 20.99, 21, 750.0, 1));
  PremiumCustomer premium_customer("PremiumCustomer", "somewhere");

  premium_customer.AddToCart("1", prod_01);
  premium_customer.AddToCart("2", prod_02);
  premium_customer.AddToCart("3", prod_03);

  EXPECT_TRUE(premium_customer.FindProduct("1"));
}

TEST(CustomerTester, FindProductFalse)
{
  uniquePtr<Product> prod_01(new Toy("Teddy", "Sc. Toy", 24, 6, 3));
  uniquePtr<Product> prod_02(new Toy("MatchBox", "Sc. Toy", 50, 3, 3));
  uniquePtr<Product> prod_03(new Alcoholic("Vodka", 20.99, 21, 750.0, 1));
  PremiumCustomer premium_customer("PremiumCustomer", "somewhere");

  premium_customer.AddToCart("1", prod_01);
  premium_customer.AddToCart("2", prod_02);
  premium_customer.AddToCart("3", prod_03);

  EXPECT_FALSE(premium_customer.FindProduct("69"));
}