#ifndef _RESTAURANT_CAESAR_SALAD_H_
#define _RESTAURANT_CAESAR_SALAD_H_

#include "dish.h"

class CaesarSalad : public Dish
{
public:
  CaesarSalad(std::string name) : Dish(name) {}
};

#endif