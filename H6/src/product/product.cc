#include "../../include/product/product.h"

#include <exception>

Product::Product(const std::string& name, double price, uint32_t quantity)
    : name_(name), price_(price), quantity_(quantity){}

bool Product::IsEmpty() const{
  return name_.empty() && price_ == 0.0 && quantity_ == 0;
}

void Product::Print(std::ostream& out) {
  if(this->IsEmpty()){
    throw std::out_of_range("Print product: try to print an empty Product object.");
  }
  out << name_ << ", price = " << price_ << ", quantity = " << quantity_ << "\n";
}
