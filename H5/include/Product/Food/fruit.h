#ifndef _GENERAL_STORE_FRUIT_H_
#define _GENERAL_STORE_FRUIT_H_

#include "food.h"

class Fruit : public Food
{
public:
  Fruit(std::string name, double price)
    : Food(name, price) {}
};

#endif