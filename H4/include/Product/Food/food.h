#ifndef _GENERAL_STORE_FOOD_H_
#define _GENERAL_STORE_FOOD_H_

#include "../include/Product/product.h"

class Food : public Product
{
public:
  Food(std::string name, double price)
    : Product(name, price) {}
};

#endif