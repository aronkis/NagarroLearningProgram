#include "../include/Product/Drink/alcoholic.h"
#include "../include/Product/product.h"
#include "../include/Client/client.h"
#include "../include/store.h"

Cart::iterator Client::FindInCart(std::shared_ptr<Product> product)
{
  for (auto result = cart_.begin(); result != cart_.end(); result++)
  {
    if (result->first == product)
      return result;
  }
  return cart_.end();
}

bool isName(const std::string& name)
{
  for (char ch: name)
  {
    if (!isalpha(ch))
    {
      return false;
    }
  }
  return true;
}

Client::Client(std::string name, int age, double balance, double discount)
{
  if (!isName(name))
  {
    throw std::invalid_argument("Name cannot contain numbers or special characters!");
  }
  else
  {
    name_ = name;
  }

  if (age < 0 || age > 130)
  {
    throw std::invalid_argument("Age cannot be less 0 or more than 130!");
  }
  else
  {
    age_ = age;
  }
  
  if (balance < 0)
  {
    throw std::invalid_argument("Balance cannot be less than 0!");
  }
  else
  {
    balance_ = balance;
  }
  
  discount_ = discount;
}

void Client::AddToCart(std::shared_ptr<Product> product, Store* store)
{
  if (age_ >= 18 || (std::dynamic_pointer_cast<Alcoholic>(product) == nullptr))
  {
    auto inv_it = store->FindInStore(product);
    if (inv_it->second == 0 && inv_it != store->GetInventory().end())
    {
      throw std::range_error("The product is currently not available");
    }
    else if (inv_it == store->GetInventory().end())
    {
      throw std::range_error("We do not have this product!");
    }
    else
    {
      auto cart_it = FindInCart(product);
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

double Client::GetTotal()
{
  double total = 0.0;
  for (auto& prod : cart_)
  {
    total += prod.first->GetPrice() * prod.second;
  }
  return total - (total * discount_);
}

void Client::Pay(double total)
{
  if (balance_ < total)
  {
    throw std::out_of_range("Not enough balance!");
  }
  else
  {
    balance_ -= total;
  }
}