#include "../../include/product/alcoholic.h"

#include <exception>

Alcoholic::Alcoholic(const std::string& name, double price, uint8_t age_limit, 
		     float liquid_volume, uint32_t quantity)
    : Product(name, price, quantity), age_limit_(age_limit), 
      liquid_volume_(liquid_volume){}

void Alcoholic::Print(std::ostream& out){
  if(this->IsEmpty()){
    throw std::out_of_range("Print product: try to print an empty Product object.");
  }
  out << name_ << ", price = " << price_ << ", quantity: " << quantity_;
  out << "\n" << int(age_limit_) << "+ " << ", " << "volume: " << liquid_volume_ << "\n";
}
