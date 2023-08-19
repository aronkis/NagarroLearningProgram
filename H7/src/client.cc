#include "../include/client/client.h"

#include <cstdlib>
#include <chrono>	
#include <thread>
#include <iostream>

void Client::Eat()
{
  int time_to_eat = rand() % 10;
  std::cout << "Client: " << id_ << " is eating for: " << time_to_eat << " milliseconds.\n";
  std::this_thread::sleep_for(std::chrono::milliseconds(time_to_eat));
  std::cout << "Client: " << id_ << " is now leaving.\n";
}

std::unique_ptr<Dish> Client::orderDish()
{
  int order_number = rand() % 4;
  switch (order_number)
  {
  case 0:
    return std::make_unique<CaesarSalad>("Caesar Salad");
    break;
  case 1:
    return std::make_unique<MisoRamen>("Miso Ramen");
    break;
  case 2:
    return std::make_unique<Steak>("Steak");
    break;
  default:
    return std::make_unique<RicePudding>("Rice Pudding");
    break;
  }
}