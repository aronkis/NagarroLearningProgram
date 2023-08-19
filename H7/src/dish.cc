#include "../include/menu/dish.h"

#include <chrono>	
#include <thread>
#include <iostream>

void Dish::Prepare()
{
  int time_to_prepare = rand() % 10;
  std::cout << name_ << " is being prepared for: " << time_to_prepare << " milliseconds.\n";
  std::this_thread::sleep_for(std::chrono::milliseconds(time_to_prepare));
  std::cout << name_ << " is done.\n";
}