#include "../../include/customer/underage_customer.h"

#include <exception>

#include "../../include/product/alcoholic.h"
#include "../../include/product/toy.h"

UnderageCustomer::UnderageCustomer(const std::string& name, 
		     		   const std::string& address,
                                   uniquePtr<Customer>& guardian, 
				   double discount)
    : Customer(name, address), discount_(discount), guardian_(std::move(guardian)){}

double UnderageCustomer::CompletePurchase(Store& store){
  if(shopping_cart_.empty()){
    throw std::runtime_error("Can't complete your purchases. Shopping cart is empty!");
  }
  double amount = 0.0;
  double temp = 0.0;
  for(const auto& [id, product] : shopping_cart_){
    if(product.get() == dynamic_cast<Toy*>(product.get())){
        temp =  store.SellProduct(id, product->GetQuantity());
        amount += temp - (temp * discount_);
    }
    if(product.get() != dynamic_cast<Alcoholic*>(product.get())){
        amount += store.SellProduct(id, product->GetQuantity());
    }
  }
  ClearShoppingCart();
  store.AddIncome(amount);
  return amount; 
}

void UnderageCustomer::Print(std::ostream& out){
  if(this->IsEmpty()){
    throw std::out_of_range("Print customer: try to print an empty Customer object.");
  }
  out << "client: " << name_ << ", " << address_ << "\n";
  out << "discount_ " << discount_*10 << "%" << "\n";
  if(!shopping_cart_.empty()){
    out << "shopping cart:\n";
    for(const auto& item : shopping_cart_){
      out << item.first << ": ";
      item.second->Print(out);
    }
  }
}