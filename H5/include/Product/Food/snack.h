#ifndef _GENERAL_STORE_SNACK_H_
#define _GENERAL_STORE_SNACK_H_

#include "food.h"

class Snack : public Food
{
public:
  Snack(std::string name, double price)
    : Food(name, price) {}
};

#endif