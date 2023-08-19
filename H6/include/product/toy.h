#ifndef STORE_SIMULATOR_INCLUDE_PRODUCT_TOY_H_
#define STORE_SIMULATOR_INCLUDE_PRODUCT_TOY_H_

#include <ostream>
#include <cstdint>
#include <string>

#include "product.h"

class Toy: public Product{
  public:
    Toy(const std::string& name,  const std::string& manufacturer, 
        double price, uint8_t age_limit, uint32_t quantity);
    void Print(std::ostream& out) override;
    void SetAgeLimit(uint8_t age);
    void SetManufacturer(const std::string& manufacturer);
    uint8_t GetAgeLimit() const;
    const std::string& GetManufacturer() const;
  private:
    uint8_t age_limit_;
    std::string manufacturer_;
};
inline void Toy::SetAgeLimit(uint8_t age){
  age_limit_ = age;
}
inline void Toy::SetManufacturer(const std::string& manufacturer){
  manufacturer_ = manufacturer;
}
inline uint8_t Toy::GetAgeLimit() const{
  return age_limit_;
}
inline const std::string& Toy::GetManufacturer() const{
  return manufacturer_;
}
#endif  // STORE_SIMULATOR_INCLUDE_PRODUCT_TOY_H_
