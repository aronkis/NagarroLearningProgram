#include "../../include/product/toy.h"

#include <exception>

Toy::Toy(const std::string& name, const std::string& manufacturer, 
	 double price, uint8_t age_limit, uint32_t quantity)
    : Product(name, price, quantity), age_limit_(age_limit), 
      manufacturer_(manufacturer){}

void Toy::Print(std::ostream& out){
  if(this->IsEmpty()){
    throw std::out_of_range("Print product: try to print an empty Product object.");
  }
  out << name_ << ", price = " << price_ << ", quantity = " << quantity_;
  out << "\n" << int(age_limit_) << "+ " << "manufacturer: " << manufacturer_ << "\n";
}
