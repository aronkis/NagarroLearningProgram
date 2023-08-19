#include <iostream>
#include "include/store.h"
#include "include/printer.h"
#include "include/Client/client.h"
#include "include/Client/regular_client.h"
#include "include/Product/Food/snack.h"
#include "include/Product/Food/fruit.h"
#include "include/Product/Drink/alcoholic.h"
#include "include/Product/Drink/non_alcoholic.h"

void addProds(std::shared_ptr<Store> store, std::shared_ptr<Product> product, int count)
{
  for (int i = 0; i < count; i++)
  {
    store->AddToStore(product);
  }
}

int main()
{
  Printer printer;
  
  std::shared_ptr<Fruit> apple = std::make_shared<Fruit>("Apple", 2);
  std::shared_ptr<Alcoholic> beer = std::make_shared<Alcoholic>("Beer", 4);
  std::shared_ptr<Snack> chips = std::make_shared<Snack>("Chips", 7);
  std::shared_ptr<NonAlcoholic> water = std::make_shared<NonAlcoholic>("Water", 2);
  std::shared_ptr<Store> store = std::make_shared<Store>("ABC", 10);

  addProds(store, apple, 2);
  addProds(store, beer, 2);
  addProds(store, chips, 3);
  addProds(store, water, 5);

  std::cout << "The store has: \n";
  printer.print(store);

  std::shared_ptr<RegularClient> client = std::make_shared<RegularClient>("John", 17, 100);

  std:: cout << "\n\nClient added to cart:\n";
  if (client->AddToCart(apple, store))
  {
    std::cout << apple->GetName() << " added succesfully!\n";
  }
  else 
  {
    std::cout << apple->GetName() << " cannot be added!\n";
  }

  if (client->AddToCart(apple, store))
  {
    std::cout << apple->GetName() << " added succesfully!\n";
  }
  else 
  {
    std::cout << apple->GetName() << " cannot be added!\n";
  }

  if (client->AddToCart(chips, store))
  {
    std::cout << chips->GetName() << " added succesfully!\n";
  }
  else 
  {
    std::cout << chips->GetName() << " cannot be added!\n";
  }

  if (client->AddToCart(chips, store))
  {
    std::cout << chips->GetName() << " added succesfully!\n";
  }
  else 
  {
    std::cout << chips->GetName() << " cannot be added!\n";
  }

  if (client->AddToCart(beer, store))
  {
    std::cout << beer->GetName() << " added succesfully!\n";
  }
  else 
  {
    std::cout << beer->GetName() << " cannot be added!\n";
  }
  if (client->AddToCart(apple, store))
  {
    std::cout << apple->GetName() << " added succesfully!\n";
  }
  else 
  {
    std::cout << apple->GetName() << " cannot be added!\n";
  }

  if (client->AddToCart(water, store))
  {
    std::cout << water->GetName() << " added succesfully!\n";
  }
  else 
  {
    std::cout << water->GetName() << " cannot be added!\n";
  }

  std::cout << "\n";
  printer.print(client);
  std::cout << "\n";

  if (store->CheckOut(client))
  {
    std::cout << "Purchase succesful!\n";
  }
  else
  {
    std::cout << "Purchase unsuccesful\n";
  }


  std::cout << std::endl;
  printer.print(store);
  std::cout << "\nThe store's balance: " << store->GetBalance() << std::endl;

}