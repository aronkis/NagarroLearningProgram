#include "../../include/customer/affiliate_customer.h"

#include <exception>

AffiliateCustomer::AffiliateCustomer(const std::string &name, 
				     const std::string &address, 
				     uint32_t points)
    : Customer(name, address), points_(points){}
  
double AffiliateCustomer::CompletePurchase(Store &store){
  if(shopping_cart_.empty()){
    throw std::runtime_error("Can't complete your purchases. Shopping cart is empty!");
  }
  double amount = 0.0;
  for (const auto& [id, product] : shopping_cart_) {
    amount += store.SellProduct(id, product->GetQuantity());
  }
  // use points as discount (10 point = 1 money unit)
  amount -= points_ / 10;
  points_ += amount / 50; // each 50 money unit = 1 point
  store.AddIncome(amount);
  return amount;
}

void AffiliateCustomer::Print(std::ostream& out){
  if(this->IsEmpty()){
    throw std::out_of_range("Print customer: try to print an empty Customer object.");
  }
  out << "client: " << name_ << ", " << address_ << "\n";
  out << "loyalty points: " << points_ << "\n";
  if(!shopping_cart_.empty()){
    out << "shopping cart:\n";
    for(const auto& item : shopping_cart_){
      out << item.first << ": ";
      item.second->Print(out);
    }
  }
}