#include "../include/store.h"
#include "../include/Client/client.h"
#include "../include/Product/product.h"
#include "../include/Product/Drink/alcoholic.h"

Cart::iterator Client::FindInCart(std::shared_ptr<Product> product)
{
  Cart::iterator result;
  for (result = cart_.begin(); result != cart_.end(); result++)
  {
    if (result->first == product)
      return result;
  }
  return result;
}

bool Client::AddToCart(std::shared_ptr<Product> product, std::shared_ptr<Store> store)
{
  if (age_ >= 18 || (std::dynamic_pointer_cast<Alcoholic>(product) == nullptr))
  {
    Inventory::iterator inv_it = store->FindInStore(product);
    if (inv_it->second == 0 && inv_it != store->GetInventory().end())
    {
      return false;
    }
    else
    {
      Cart::iterator cart_it = FindInCart(product);
      if (cart_it != cart_.end())
      {
        cart_it->second++;
      }
      else
      {
        cart_.emplace_back(std::make_pair(product, 1));
      }
      inv_it->second--;
      return true;
    }
  }
  return false;
}

double Client::GetTotal()
{
  double total = 0.0;
  for (auto& prod : cart_)
  {
    total += prod.first->GetPrice() * prod.second;
  }
  return total;
}

bool Client::Pay(double total)
{
  if (balance_ > total)
  {
    balance_ -= total;
    return true;
  }
  else
  {
    return false;
  }
}
