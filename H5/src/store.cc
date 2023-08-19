#include <iostream>
#include "../include/store.h"
#include "../include/Client/client.h"
#include "../include/Product/product.h"

Inventory::iterator Store::FindInStore(std::shared_ptr<Product> product)
{
  for (auto result = inventory_.begin(); result != inventory_.end(); result++)
  {
    if (result->first == product)
      return result;
  }
  return inventory_.end();
}

Store::Store(std::string name, double balance)
{
  name_ = name;
  if (balance < 0)
  {
    throw std::invalid_argument("The store balance cannot be less than 0!");
  }
  else
  {
    balance_ = balance;
  }
}

void Store::AddToStore(std::shared_ptr<Product> product, int quantity)
{
  auto result = FindInStore(product);
  if (result != inventory_.end())
  {
    result->second += quantity;
  }
  else
  {
    inventory_.emplace_back(std::make_pair(product, quantity));
  }
}

void Store::RemoveFromStore(std::shared_ptr<Product> product)
{
  auto result = FindInStore(product);
  if (result != inventory_.end())
  {
    inventory_.erase(result);
  }
}

void Store::CheckOut(std::shared_ptr<Client> client)
{
  Cart::iterator it;
  Cart cart_ = client->GetCart();
  double total = client->GetTotal();
  try
  {
    client->Pay(total);
    balance_ += total;
  }
  catch(const std::exception& e) // if not enough balance put the products back to store
  {
    for (auto& [prod, quantity]: client.get()->GetCart())
    {
      AddToStore(prod, quantity);
    }
    std::cerr << e.what() << '\n';
  }
}