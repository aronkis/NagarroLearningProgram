#ifndef STORE_SIMULATION_INCLUDE_CUSTOMER_CUSTOMER_H_
#define STORE_SIMULATION_INCLUDE_CUSTOMER_CUSTOMER_H_

#include <ostream>
#include <cstdint>
#include <unordered_map>
#include <string>

#include "../product/product.h"
#include "../printer/printable.h"
#include "../store.h"
#include "../unique.hpp"

class Customer: public Printable{
  public:
    Customer(const std::string& name, const std::string& address);
    // return the amount that customer have to pay
    virtual double CompletePurchase(Store& store);
    void AddToCart(const std::string& id, uniquePtr<Product>& product);
    bool ClearShoppingCart();
    // remove the no. of product from customer shopping cart
    void RemoveProduct(const std::string& id, uint8_t quantity = 0);
    bool IsEmpty() const;
    bool FindProduct(const std::string& id);
    Product* GetProduct(const std::string& id);
    void Print(std::ostream& out) override;
    void SetName(const std::string& name);
    void SetAddress(const std::string& address);
    void SetShoppingCart(std::unordered_map<std::string, uniquePtr<Product>>& shopping_cart);
    const std::string& GetName() const;
    const std::string& GetAddress() const;
    const std::unordered_map<std::string, uniquePtr<Product>>& GetShoppingCart() const;
  protected:
    std::string name_;
    std::string address_;
    // std::unordered_map<indetifier, product>
    std::unordered_map<std::string, uniquePtr<Product>> shopping_cart_;
};
inline void Customer::SetName(const std::string& name){
  name_ = name;
}
inline void Customer::SetAddress(const std::string& address){
  address_ = address;
}
inline void Customer::SetShoppingCart(
    std::unordered_map<std::string, uniquePtr<Product>>& shopping_cart){
  shopping_cart_ = std::move(shopping_cart);
}
inline const std::string& Customer::GetName() const{
  return name_;
}
inline const std::string& Customer::GetAddress() const{
  return address_;
}
inline const std::unordered_map<std::string, uniquePtr<Product>>& Customer::GetShoppingCart() const{
  return shopping_cart_;
}
#endif  // STORE_SIMULATION_INCLUDE_CUSTOMER_CUSTOMER_H_
