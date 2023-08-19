#ifndef STORE_SIMULATOR_INCLUDE_PRODUCT_ALCOHOLIC_H_
#define STORE_SIMULATOR_INCLUDE_PRODUCT_ALCOHOLIC_H_

#include <ostream>
#include <cstdint>
#include <string>

#include "./product.h"

class Alcoholic: public Product{
  public:
    Alcoholic(const std::string& name, double price, uint8_t age_limit, 
	      float liquid_volume, uint32_t quantity);
    void SetAgeLimit(uint8_t age);
    void SetLiquidAmount(float liquid_volume);
    uint8_t GetAgeLimit() const;
    float GetLiquidAmount() const;
    void Print(std::ostream& out) override;
  private:
    uint8_t age_limit_;
    float liquid_volume_;
};
inline void Alcoholic::SetAgeLimit(uint8_t age){
  age_limit_ = age;
}
inline void Alcoholic::SetLiquidAmount(float liquid_volume){
  liquid_volume_ = liquid_volume;
}
inline uint8_t Alcoholic::GetAgeLimit() const{
  return age_limit_;
}
inline float Alcoholic::GetLiquidAmount() const{
  return liquid_volume_;
}
#endif  // STORE_SIMULATOR_INCLUDE_PRODUCT_ALCOHOLIC_H_