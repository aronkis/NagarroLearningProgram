#include <gtest/gtest.h>
#include <string>
#include <unordered_map>
#include <fstream>

#include "../include/printers_header.h"
#include "../include/products_header.h"
#include "../include/customers_header.h"
#include "../include/unique.hpp"

TEST(PrinterTester, ConsolePrint)
{
  testing::internal::CaptureStdout();
  uniquePtr<Printer> printer(new ConsolePrinter);
  uniquePtr<Product> prod_01(new Product("Product", 59, 1));
  PremiumCustomer premium_customer("PremiumCustomer", "somewhere");

  premium_customer.AddToCart("1", prod_01);

  printer->Print(premium_customer);  // can throw an error

  std::string output = testing::internal::GetCapturedStdout();
  std::string expected_output = "client: PremiumCustomer, somewhere\ndiscount: 1%\nshopping cart:\n1: Product, price = 59, quantity = 1\n\n";

  EXPECT_STREQ(output.c_str(), expected_output.c_str());
}

TEST(PrinterTester, FilePrint)
{
  uniquePtr<Product> prod_01(new Product("Product", 59, 1));
  PremiumCustomer premium_customer("PremiumCustomer", "somewhere");

  premium_customer.AddToCart("1", prod_01);

  uniquePtr<Printer> printer(new FilePrinter("../data/out_file.txt", "w"));
  printer->Print(premium_customer);
  
  std::ifstream file("../data/out_file.txt");
  std::string output;
  if (file.is_open())
  {
    while (!file.eof())
    {
      std::string read;
      file >> read;
      output += read;
    }
  }

  std::string expected_output = "client:PremiumCustomer,somewherediscount:1%shoppingcart:1:Product,price=59,quantity=1";
  EXPECT_STREQ(expected_output.c_str(), output.c_str());
}