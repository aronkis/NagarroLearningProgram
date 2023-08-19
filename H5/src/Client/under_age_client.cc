#include "../include/Client/under_age_client.h"
#include "../include/Product/Drink/alcoholic.h"
#include "../include/Product/product.h"
#include "../include/store.h"

void UnderAge::AddToCart(std::shared_ptr<Product> product, Store* store)
{
  if (std::dynamic_pointer_cast<Alcoholic>(product) == nullptr)
  {
    Inventory::iterator inv_it = store->FindInStore(product);
    if (inv_it->second == 0 && inv_it != store->GetInventory().end())
    {
      throw std::range_error("The product is not available in this store!");
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
    }
  }
  else
  {
    throw std::domain_error("UnderAge client cannot buy restricted products!");
  }
}
