#ifndef _RESTAURANT_RICE_PUDDING_H_
#define _RESTAURANT_RICE_PUDDING_H_

#include "dish.h"

class RicePudding : public Dish
{
public:
  RicePudding(std::string name) : Dish(name) {}
};

#endif