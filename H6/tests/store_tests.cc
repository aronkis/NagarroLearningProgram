#include <gtest/gtest.h>

#include <iostream>
#include <exception>
#include <string>
#include <unordered_map>

#include "../include/printers_header.h"
#include "../include/products_header.h"
#include "../include/customers_header.h"
#include "../include/store.h"
#include "../include/unique.hpp"

TEST(StoreTester, AddProduct)
{
  std::unordered_map<std::string, uniquePtr<Product>> items;
  Store store("MyStore","somewhere",items);
  uniquePtr<Product> prod_01(new Toy("Teddy", "Sc. Toy", 24, 6, 120));
  uniquePtr<Product> prod_02(new Alcoholic("Vodka", 20.99, 21, 750.0, 45));
  uniquePtr<Product> prod_03(new Book("CleanCode", 320, "Rober C. Martin", 340, 5));

  store.AddProduct(prod_01,"cod_prod_1");
  store.AddProduct(prod_02,"cod_prod_2");
  store.AddProduct(prod_03,"cod_prod_3");

  EXPECT_EQ(store.GetInventory().size(), 3);
}

TEST(StoreTester, RemoveProduct)
{
  std::unordered_map<std::string, uniquePtr<Product>> items;
  Store store("MyStore","somewhere",items);
  uniquePtr<Product> prod_01(new Toy("Teddy", "Sc. Toy", 24, 6, 120));

  store.AddProduct(prod_01,"cod_prod_1");

  store.RemoveProduct("cod_prod_1", 25);

  EXPECT_EQ(store.GetInventory().at("cod_prod_1").get()->GetQuantity(), 95);
}

TEST(StoreTester, SellProduct)
{
  std::unordered_map<std::string, uniquePtr<Product>> items;
  Store store("MyStore","somewhere",items);
  uniquePtr<Product> prod_01(new Toy("Teddy", "Sc. Toy", 24, 6, 120));

  store.AddProduct(prod_01,"cod_prod_1");

  double value = store.SellProduct("cod_prod_1", 25);

  EXPECT_DOUBLE_EQ(value, 600);
}

TEST(StoreTester, AddIncome)
{
  std::unordered_map<std::string, uniquePtr<Product>> items;
  Store store("MyStore","somewhere",items);

  store.AddIncome(420);

  EXPECT_DOUBLE_EQ(store.GetIncome(), 420);
}

TEST(StoreTester, AskForSuccess)
{
  std::unordered_map<std::string, uniquePtr<Product>> items;
  Store store("MyStore","somewhere",items);
  uniquePtr<Product> prod_01(new Toy("Teddy", "Sc. Toy", 24, 6, 120));

  store.AddProduct(prod_01,"cod_prod_1");

  Status asked_product_success = store.AskFor("Teddy", 10);  
  EXPECT_EQ(asked_product_success, Status::Succes);
}

TEST(StoreTester, AskForLessQuantity)
{
  std::unordered_map<std::string, uniquePtr<Product>> items;
  Store store("MyStore","somewhere",items);
  uniquePtr<Product> prod_01(new Toy("Teddy", "Sc. Toy", 24, 6, 120));

  store.AddProduct(prod_01,"cod_prod_1");

  Status asked_product_less_quantity = store.AskFor("Teddy", 130);
  EXPECT_EQ(asked_product_less_quantity, Status::LessQuantity);
}

TEST(StoreTester, AskForNotFound)
{
  std::unordered_map<std::string, uniquePtr<Product>> items;
  Store store("MyStore","somewhere",items);
  uniquePtr<Product> prod_01(new Toy("Teddy", "Sc. Toy", 24, 6, 120));

  store.AddProduct(prod_01,"cod_prod_1");

  Status asked_product_not_found = store.AskFor("TeddyX", 130);
  EXPECT_EQ(asked_product_not_found, Status::NotFound);
}

TEST(StoreTester, IsEmptyTrue)
{
  std::unordered_map<std::string, uniquePtr<Product>> items;
  Store store("","",items);

  EXPECT_TRUE(store.IsEmpty());
}

TEST(StoreTester, IsEmptyFalse)
{
  std::unordered_map<std::string, uniquePtr<Product>> items;
  Store store("this","that",items);

  EXPECT_FALSE(store.IsEmpty());
}


TEST(StoreTester, FindProductTrue)
{
  std::unordered_map<std::string, uniquePtr<Product>> items;
  Store store("MyStore","somewhere",items);
  uniquePtr<Product> prod_01(new Toy("Teddy", "Sc. Toy", 24, 6, 120));

  store.AddProduct(prod_01, "cod_prod_1");

  bool found = store.FindProduct("cod_prod_1");

  EXPECT_TRUE(found);
}

TEST(StoreTester, FindProductFalse)
{
  std::unordered_map<std::string, uniquePtr<Product>> items;
  Store store("MyStore","somewhere",items);
  uniquePtr<Product> prod_01(new Toy("Teddy", "Sc. Toy", 24, 6, 120));

  store.AddProduct(prod_01, "cod_prod_1");

  bool found = store.FindProduct("cod_prod_2");

  EXPECT_FALSE(found);
}
