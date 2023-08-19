#ifndef _RESTAURANT_DISH_H_
#define _RESTAURANT_DISH_H_

#include <string>

class Dish
{
public:
  Dish(std::string name) : name_(name) {}
  void Prepare();
  inline std::string GetName() const { return name_; }

private:
  std::string name_;
};

#endif