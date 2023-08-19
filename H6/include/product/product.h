#ifndef STORE_SIMULATION_INCLUDE_PRODUCT_PRODUCT_H_
#define STORE_SIMULATION_INCLUDE_PRODUCT_PRODUCT_H_

#include <ostream>
#include <cstdint>
#include <string>

#include "../printer/printable.h"

class Product: public Printable{
  public:
    Product(const std::string& name, double price, uint32_t quantity);
    bool IsEmpty() const;
    void Print(std::ostream& out) override;
    void SetName(const std::string& name);
    void SetPrice(double price);
    void SetQuantity(uint32_t quantity);
    const std::string& GetName() const;
    double GetPrice() const;
    uint32_t GetQuantity() const;
  protected:
    std::string name_;
    double price_;
    uint32_t quantity_;
};
inline void Product::SetName(const std::string& name){
  name_ = name;
}
inline void Product::SetPrice(double price){
  price_ = price;
}
inline void Product::SetQuantity(uint32_t quantity){
  quantity_ = quantity;
}
inline const std::string& Product::GetName() const{
  return name_;
}
inline double Product::GetPrice() const{
  return price_;
}
inline uint32_t Product::GetQuantity() const{
  return quantity_;
}
#endif  // STORE_SIMULATION_INCLUDE_PRODUCT_PRODUCT_H_