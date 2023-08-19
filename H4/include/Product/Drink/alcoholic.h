#ifndef _GENERAL_STORE_ALCOHOLIC_H_
#define _GENERAL_STORE_ALCOHOLIC_H_

#include "beverage.h"

class Alcoholic : public Beverage
{
public:
  Alcoholic(std::string name, double price) 
    : Beverage(name, price, true) {}
};

#endif