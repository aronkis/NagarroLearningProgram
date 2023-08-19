#ifndef _RESTAURANT_STREAK_H_
#define _RESTAURANT_STREAK_H_

#include "dish.h"

class Steak : public Dish
{
public:
  Steak(std::string name) : Dish(name) {}
};

#endif