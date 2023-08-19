#ifndef _GENERAL_STORE_BEVERAGE_H_
#define _GENERAL_STORE_BEVERAGE_H_

#include "../include/Product/product.h"

class Beverage : public Product
{
public:
  Beverage(std::string name, double price, bool restricted)
    : Product(name, price), restricted_(restricted) {}
protected: 
  bool restricted_ = false;
};

#endif