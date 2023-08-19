#ifndef _RESTAURANT_MISO_RAMEN_H_
#define _RESTAURANT_MISO_RAMEN_H_

#include "dish.h"

class MisoRamen : public Dish
{
public:
  MisoRamen(std::string name) : Dish(name) {}
};

#endif