#include "./include/food.h"
#include "./include/client/client.h"
#include "./include/restaurant/restaurant.h"

#include <iostream>
#include <thread>

std::mutex dish_mutex, client_mutex;
std::condition_variable dish_cond_var, client_cond_var;
Dishes dishes;
Restaurant restaurant("Restaurant", 5);

void simulation(int id)
{
  Client client(id);
  restaurant.ReserveTable(client_mutex, client_cond_var);
  std::unique_ptr<Dish> dish = client.orderDish();
  
  std::cout<<"Client " << id << " asks for " << dish->GetName() << ".\n";

  restaurant.MakeDish(dishes, dish, dish_mutex, dish_cond_var); 
  
  restaurant.ServeDish(dishes, dish, dish_mutex, dish_cond_var); 

  client.Eat(); 
  
  restaurant.LeaveTable(client_mutex, client_cond_var); 
}

int main()
{
    std::cout << "Opening the restaurant.\n";
    srand(time(NULL));
    std::thread clients[5];
    
    for (int i = 0; i < 5; i++)
        clients[i] = std::thread(&simulation, i);

    for (int i = 0; i < 5; i++)
        clients[i].join();

  std::cout << "Closing the restaurant.\n";
}