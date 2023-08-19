#ifndef _RESTAURANT_CLIENT_H_
#define _RESTAURANT_CLIENT_H_

#include "../include/food.h"
#include <memory>

class Client
{
public:
  Client (int id) : id_(id) {}
  void Eat();
  std::unique_ptr<Dish> orderDish();
  inline int GetId() const { return id_; }
  
private:
  int id_;
};

#endif