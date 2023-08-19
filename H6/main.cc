#include <iostream>
#include <exception>
#include <string>
#include <unordered_map>

#include "./include/printers_header.h"
#include "./include/products_header.h"
#include "./include/customers_header.h"
#include "./include/store.h"
#include "./include/unique.hpp"

// logger initialization
FileHandler Logger::log_("data/log.txt");

int main(){
  Logger::Log("Multiple ","argument ","log ","test",".");
  std::unordered_map<std::string, uniquePtr<Product>> items;
  uniquePtr<Printer> printer(new ConsolePrinter);

  // Test if I try to print empty objects
  {
    Store store("","",items);
    try{
      printer->Print(store);  // can throw an error
    }
    catch(std::runtime_error& e){
      Logger::Log(e.what());
    }
  }

  Store store("MyStore","somewhere",items);
  // create products and try to insert an empty Product object
  {
    uniquePtr<Product> prod_01(new Toy("Teddy", "Sc. Toy", 24, 6, 120));
    uniquePtr<Product> prod_02(new Alcoholic("Vodka", 20.99, 21, 750.0, 45));
    uniquePtr<Product> prod_03(new Book("CleanCode", 320, "Rober C. Martin", 340, 5));
    uniquePtr<Product> empty_product(new Product("", 0.0, 0));
   
    // initiliaze a store
    try{
      store.AddProduct(prod_01,"cod_prod_1");
      store.AddProduct(prod_02,"cod_prod_2");
      store.AddProduct(prod_03,"cod_prod_3");
      store.AddProduct(empty_product,"cod_prod_4");
    }
    catch (std::invalid_argument& e){
      Logger::Log(e.what());
    }
    
    try{
      printer->Print(store);  // can throw an error
    }
    catch(std::runtime_error& e){
      Logger::Log(e.what());
    }
  }

  // create a Customers and make some purchases
  {
    uniquePtr<Product> prod_01(new Toy("Teddy", "Sc. Toy", 24, 6, 3));
    uniquePtr<Product> prod_02(new Alcoholic("Vodka", 20.99, 21, 750.0, 1));
    PremiumCustomer premium_customer("PremiumCustomer", "somewhere");
    
    try{
      premium_customer.AddToCart("cod_prod_1", prod_01);
      premium_customer.AddToCart("cod_prod_2",prod_02);
    }
    catch (std::invalid_argument& e){
      Logger::Log(e.what());
    }

    try{
      printer->Print(premium_customer);  // can throw an error
      printer.reset(new FilePrinter("course_5_homework/data/out_file.txt"));
      printer->Print(premium_customer);
    }
    catch(std::runtime_error& e){
      Logger::Log(e.what());
    }
    try{
      std::cout << "Premium customer has to pay: " << premium_customer.CompletePurchase(store) << "\n";
      premium_customer.CompletePurchase(store); // try to complete purchases process again (shopping cart will be empty)
    }
    catch (std::runtime_error& e){
      Logger::Log(e.what());
    }
  }
  return 0;
}