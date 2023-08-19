#ifndef _GENERAL_STORE_UNDER_AGE_CLIENT_H_
#define _GENERAL_STORE_UNDER_AGE_CLIENT_H_

#include "client.h"

class UnderAge : public Client
{
public:
  UnderAge(std::string name, int age, double balance)
    : Client(name, age, balance, 0.0) 
  {
    if (age > 17)
    {
      throw std::invalid_argument("Age must be less than 18!");
    }
  }
  void AddToCart(std::shared_ptr<Product> product, Store* store) override;
};

#endif
