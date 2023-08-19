#include "../include/printer.h"
#include "../include/Client/client.h"
#include "../include/Product/product.h"
#include "../include/store.h"

void Printer::print(const std::shared_ptr<Client> client) const
{

  std::cout << "Client Name: " << client->GetName() << " and has in cart:" << std::endl;
  for (auto& cli: client->GetCart())
  {
    std::cout << cli.first->GetName() << " " << cli.second << "x\n";
  }
}

void Printer::print(const std::shared_ptr<Store> store) const
{
  for (auto& product : store->GetInventory())
  {
    std::cout << "Item: " << product.first->GetName()
              << "; price: " << product.first->GetPrice()
              << "; quantity: " << product.second << std::endl;
  }
}