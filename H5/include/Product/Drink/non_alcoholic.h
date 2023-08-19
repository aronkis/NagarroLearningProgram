#ifndef _GENERAL_STORE_NONALCOHOLIC_H_
#define _GENERAL_STORE_NONALCOHOLIC_H_

#include "beverage.h"

class NonAlcoholic : public Beverage
{
public:
  NonAlcoholic(std::string name, double price) 
    : Beverage(name, price, false) {}
};

#endif