#include "../include/Product/product.h"
#include <stdexcept>

Product::Product(std::string name, double price)
{
  name_ = name;
  if (price <= 0)
  {
    throw std::invalid_argument("Price cannot be less than 0!");
  }
  else
  {
    price_ = price;
  }
}