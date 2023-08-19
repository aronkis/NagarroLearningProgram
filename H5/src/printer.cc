#include "../include/Product/product.h"
#include "../include/Client/client.h"
#include "../include/printer.h"
#include "../include/store.h"
#include <iostream>

void Printer::print(const Client* client) const
{
  std::cout << "Client Name: " << client->GetName() << " and has in cart:" << std::endl;
  for (const auto& [product, quantity]: client->GetCart())
  {
    std::cout << product->GetName() << " " << quantity << "x\n";
  }
}

void Printer::print(const Store* store) const
{
  for (const auto& product : store->GetInventory())
  {
    std::cout << "Item: " << product.first->GetName()
              << "; price: " << product.first->GetPrice()
              << "; quantity: " << product.second << std::endl;
  }
}