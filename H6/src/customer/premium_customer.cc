#include "../../include/customer/premium_customer.h"

#include <exception>

PremiumCustomer::PremiumCustomer(const std::string& name, 
				 const std::string& address, 
				 double discount)
    : Customer(name, address), discount_(discount){}

double PremiumCustomer::CompletePurchase(Store& store){
  if(shopping_cart_.empty()){
    throw std::runtime_error("Can't complete your purchases. Shopping cart is empty!");
  }
  double amount = 0.0;
  for(const auto& [id, product] : shopping_cart_){
    amount += store.SellProduct(id, product->GetQuantity());
  }
  ClearShoppingCart();
  amount -= (amount * discount_);
  store.AddIncome(amount);
  return amount;
}

void PremiumCustomer::Print(std::ostream& out){
  if(this->IsEmpty()){
    throw std::out_of_range("Print client: try to print an empty Customer object.");
  }
  out << "client: " << name_ << ", " << address_ << "\n";
  out << "discount: " << discount_*10 << "%" << "\n";
  if(!shopping_cart_.empty()){
    out << "shopping cart:\n";
    for(const auto& item : shopping_cart_){
      out << item.first << ": ";
      item.second->Print(out);
    }
  }
}
