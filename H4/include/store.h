#ifndef _GENERAL_STORE_STORE_H_
#define _GENERAL_STORE_STORE_H_

#include <list>
#include <algorithm>
#include <memory>
#include <string>

class Client;
class Product;

using Inventory = std::list<std::pair<std::shared_ptr<Product>, int>>;

class Store
{
public:
  Store(std::string name, double balance)
    : name_(name), balance_(balance) {}
  Inventory::iterator FindInStore(std::shared_ptr<Product> product);
  void AddToStore(std::shared_ptr<Product> product);
  void RemoveFromStore(std::shared_ptr<Product> product);
  void PrintInventory();
  bool CheckOut(std::shared_ptr<Client> client);
  inline double GetBalance() const { return balance_; }
  inline Inventory GetInventory() const { return inventory_; }

protected:
  std::string name_;
  double balance_;
  Inventory inventory_;
};

#endif
