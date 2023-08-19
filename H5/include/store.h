#ifndef _GENERAL_STORE_STORE_H_
#define _GENERAL_STORE_STORE_H_

#include <list>
#include <string>
#include <memory>

class Client;
class Product;

using Inventory = std::list<std::pair<std::shared_ptr<Product>, int>>;

class Store
{
public:
  Store(std::string name, double balance);
  Inventory::iterator FindInStore(std::shared_ptr<Product> product);
  void AddToStore(std::shared_ptr<Product> product, int quantity = 1);
  void RemoveFromStore(std::shared_ptr<Product> product);
  void PrintInventory();
  void CheckOut(std::shared_ptr<Client> client);
  inline double GetBalance() const { return balance_; }
  inline const Inventory& GetInventory() const { return inventory_; }

protected:
  std::string name_;
  double balance_;
  Inventory inventory_;
};

#endif
