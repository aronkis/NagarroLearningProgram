#include <iostream>
#include "include/store.h"
#include "include/printer.h"
#include "include/Client/client.h"
#include "include/Client/regular_client.h"
#include "include/Client/premium_client.h"
#include "include/Client/under_age_client.h"
#include "include/Product/Food/snack.h"
#include "include/Product/Food/fruit.h"
#include "include/Product/Drink/alcoholic.h"
#include "include/Product/Drink/non_alcoholic.h"

void addProds(Store& store, std::shared_ptr<Product> product, int count)
{
  for (int i = 0; i < count; i++)
  {
    try
    {
      store.AddToStore(product);
    }
    catch(const std::exception& e)
    {
      std::cerr << e.what() << '\n';
    }
  }
}

int main()
{
  std::shared_ptr<Product> apple;
  std::shared_ptr<Product> beer;
  std::shared_ptr<Product> chips;
  std::shared_ptr<Product> water;
  std::unique_ptr<Printer> printer = std::make_unique<Printer>();
 
  try
  {
    apple = std::make_shared<Fruit>("Apple", 2);    
  }
  catch(const std::exception& e)
  {
    std::cerr << e.what() << '\n';
  }
  
  try
  {
    beer = std::make_shared<Alcoholic>("Beer", 4);
  }
  catch(const std::exception& e)
  {
    std::cerr << e.what() << '\n';
  }
  
  try
  {
    chips = std::make_shared<Snack>("Chips", 7);
  }
  catch(const std::exception& e)
  {
    std::cerr << e.what() << '\n';
  }
  
  try
  {
    water = std::make_shared<NonAlcoholic>("Water", 2);
  }
  catch(const std::exception& e)
  {
    std::cerr << e.what() << '\n';
  }
  
  Store store("ABC", 10);
  
  addProds(store, apple, 2);
  addProds(store, beer, 2);
  addProds(store, chips, 3);
  addProds(store, water, 5);

  std::cout << "The store has: \n";
  printer->print(&store);
  std::shared_ptr<Client> client;
  
  try
  {
    client = std::make_shared<RegularClient>("John", 17, 100);
  }
  catch(const std::exception& e)
  {
    std::cerr << e.what() << "\n";
  }

  try
  {
    client->AddToCart(apple, &store);
  }
  catch(const std::exception& e)
  {
    std::cerr << e.what() << '\n';
  }
  
  try
  {
    client->AddToCart(apple, &store);
  }
  catch(const std::exception& e)
  {
    std::cerr << e.what() << '\n';
  }
  
  try
  {
    client->AddToCart(chips, &store); 
  }
  catch(const std::exception& e)
  {
    std::cerr << e.what() << '\n';
  }
  
  try
  {
    client->AddToCart(chips, &store); 
  }
  catch(const std::exception& e)
  {
    std::cerr << e.what() << '\n';
  }
  
  try
  {
    client->AddToCart(water, &store); 
  }
  catch(const std::exception& e)
  {
    std::cerr << e.what() << '\n';
  }
  
  std::cout << "\n";
  printer->print(client.get());
  std::cout << "\n";

  store.CheckOut(client);
    
  std::cout << std::endl;
  printer->print(&store);
  std::cout << "\nThe store's balance: " << store.GetBalance() << std::endl << std::endl;  
}