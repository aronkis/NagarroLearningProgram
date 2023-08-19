#ifndef STORE_SIMULATION_INCLUDE_STORE_H_
#define STORE_SIMULATION_INCLUDE_STORE_H_

#include <ostream>
#include <cstdint>
#include <string>
#include <unordered_map>

#include "./product/product.h"
#include "./unique.hpp"

class Printable;

enum class Status{
  Succes,
  LessQuantity,
  NotFound
};

class Store: public Printable{
  public:
    explicit Store(const std::string& store_name, const std::string& location, 
		   std::unordered_map<std::string, uniquePtr<Product>>& inventory,  double income = 0.0);
    void AddProduct(uniquePtr<Product>& product, const std::string& id);
    void RemoveProduct(const std::string& id, uint32_t quantity = 0);
    double SellProduct(const std::string& id, uint32_t quantity);
    void AddIncome(double amount);
    Status AskFor(const std::string& product_name, uint8_t quantity) const;
    bool IsEmpty() const;
    bool FindProduct(const std::string& id) const;
    Product* GetProduct(const std::string& id);
    void Print(std::ostream& out) override;
    void SetName(const std::string& name);
    void SetIncome(double amount);
    void SetLocation(const std::string& location);
    void SetInventory(std::unordered_map<std::string, uniquePtr<Product>>& inventory);
    double GetIncome() const;
    const std::string& GetName() const;
    const std::string& GetLocation() const;
    const std::unordered_map<std::string, uniquePtr<Product>>& GetInventory() const;
  private:
    std::string store_name_;
    std::string location_;
    double income_;
    // std::unordered_map< indetifier, product>
    std::unordered_map<std::string, uniquePtr<Product>> inventory_;
};
inline void Store::SetName(const std::string& name){
  store_name_ = name;
}
inline void Store::SetIncome(double amount){
  income_ = amount;
}
inline void Store::SetLocation(const std::string& location){
  location_ = location;
}
inline void Store::SetInventory(
    std::unordered_map<std::string, uniquePtr<Product>>& inventory){
  inventory_ = std::move(inventory);
}
inline double Store::GetIncome() const{
  return income_;
}
inline const std::string& Store::GetName() const{
  return store_name_;
}
inline const std::string& Store::GetLocation() const{
  return location_;
}
inline const std::unordered_map<std::string, uniquePtr<Product>>& Store::GetInventory() const{
  return inventory_;
}
#endif  // STORE_SIMULATION_INCLUDE_STORE_H_