#ifndef _GENERAL_STORE_CLIENT_H_
#define _GENERAL_STORE_CLIENT_H_

#include <string>
#include <list>
#include <utility>
#include <memory>

class Store;
class Product;

using Cart = std::list<std::pair<std::shared_ptr<Product>, int>>;

class Client
{
public:
  Client(std::string name, int age, double balance, double discount = 0) 
    : name_(name), age_(age), balance_(balance), discount_(discount) {}
  virtual ~Client() = default;
  inline double GetBalance() const { return balance_; }
  inline Cart GetCart() const {return cart_; }
  inline std::string GetName() const { return name_; }
  Cart::iterator FindInCart(std::shared_ptr<Product> product);
  bool Pay(double total);
  virtual bool AddToCart(std::shared_ptr<Product> product, std::shared_ptr<Store> store);
  virtual double GetTotal();

protected:
  std::string name_;
  int age_;
  double balance_;
  Cart cart_;
  double discount_ = 0.0;
};

#endif