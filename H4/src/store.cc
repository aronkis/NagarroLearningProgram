#include "../include/store.h"
#include "../include/Client/client.h"
#include "../include/Product/product.h"

Inventory::iterator Store::FindInStore(std::shared_ptr<Product> product)
{
  Inventory::iterator result;
  for (result = inventory_.begin(); result != inventory_.end(); result++)
  {
    if (result->first == product)
      return result;
  }
  return result;
}

void Store::AddToStore(std::shared_ptr<Product> product)
{
  Inventory::iterator result = FindInStore(product);
  if (result != inventory_.end())
  {
    result->second++;
  }
  else
  {
    inventory_.emplace_back(std::make_pair(product, 1));
  }
}

void Store::RemoveFromStore(std::shared_ptr<Product> product)
{
  Inventory::iterator result = FindInStore(product);
  if (result != inventory_.end())
  {
    inventory_.erase(result);
  }
}

void Store::PrintInventory()
{
  for (auto& prod: inventory_)
  {
    std::cout << "Product: " << prod.first->GetName() << " in quantity: " << prod.second << std::endl;
  }
}

bool Store::CheckOut(std::shared_ptr<Client> client)
{
  Cart::iterator it;
  Cart cart_ = client->GetCart();
  double total = client->GetTotal();
  if (client->Pay(total))
  {
    balance_ += total;
    return 1;
  }
  else
  {
    return 0;
  }
}