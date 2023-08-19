#include "../include/restaurant/restaurant.h"

#include <iostream>

void Restaurant::ReserveTable(std::mutex& client_mutex, std::condition_variable& client_cond_var)
{
    std::unique_lock<std::mutex> ulock(client_mutex);
    client_cond_var.wait(ulock, [&]()
                       { return number_of_clients_ < number_of_tables_; });
    number_of_clients_++;
    std::cout << "A table has been occupied. There are " << number_of_tables_ - number_of_clients_ << " tables empty.\n";
}

void Restaurant::MakeDish(Dishes& dishes, std::unique_ptr<Dish>& dish, std::mutex& dish_mutex,
                          std::condition_variable& dish_cond_var)
{
    std::lock_guard<std::mutex> lock(dish_mutex);
    std::cout << dish->GetName() << " is being prepared.\n";
    dish->Prepare();
    std::cout << dish->GetName() << " is ready to serve.\n";
    dishes.push(std::move(dish));
    dish_cond_var.notify_one();
}

void Restaurant::ServeDish(Dishes& dishes, const std::unique_ptr<Dish>& dish, 
                 std::mutex& dish_mutex, std::condition_variable& dish_cond_var)
{
    std::unique_lock<std::mutex> mlock(dish_mutex);
    dish_cond_var.wait(mlock, [&]()
                        { return dishes.front() == dish; });
    std::cout << dish->GetName() << "is being served.\n";
    dishes.pop();
}

void Restaurant::LeaveTable(std::mutex& client_mutex, std::condition_variable& client_cond_var)
{
    std::unique_lock<std::mutex> ulock(client_mutex);
    number_of_clients_--;
    std::cout << "A table has been released. There are " << number_of_tables_ - number_of_clients_ << " tables empty.\n";
    client_cond_var.notify_one();
}