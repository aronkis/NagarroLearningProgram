#ifndef _RESTAURANT_RESTAURANT_H_
#define _RESTAURANT_RESTAURANT_H_

#include "../food.h"
#include <queue>
#include <mutex>
#include <memory>
#include <condition_variable>
#include <atomic>

using Dishes = std::queue<std::unique_ptr<Dish>>;

class Restaurant
{
public:
  Restaurant(std::string name, int number_of_tables)
    : name_(name), number_of_tables_(number_of_tables) {}
  void ReserveTable(std::mutex& client_mutex, std::condition_variable& client_cond_var);
  void MakeDish(Dishes& dishes, std::unique_ptr<Dish>& dish, std::mutex& dish_mutex,
                std::condition_variable& dish_cond_var);
  void ServeDish(Dishes& dishes, const std::unique_ptr<Dish>& dish, 
                 std::mutex& dish_mutex, std::condition_variable& dish_cond_var);
  void LeaveTable(std::mutex& client_mutex, std::condition_variable& client_cond_var);

  
private:
  std::string name_;
  int number_of_tables_;
  std::atomic_int number_of_clients_;
};

#endif