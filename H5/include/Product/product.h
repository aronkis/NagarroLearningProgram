#ifndef _GENERAL_STORE_PRODUCT_H_
#define _GENERAL_STORE_PRODUCT_H_

#include <string>

class Product
{
public:
  Product (std::string name, double price);
  virtual ~Product() = default;

  bool operator==(const Product& other)
  {
    return name_ == other.name_ && price_ == other.price_;
  }

  inline std::string GetName() { return name_; }
  inline double GetPrice() { return price_; }

protected:
  std::string name_;
  double price_;
};

#endif