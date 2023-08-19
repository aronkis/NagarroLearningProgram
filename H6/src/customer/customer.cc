#include "../../include/customer/customer.h"

#include <exception>
#include <iostream>

Customer::Customer(const std::string& name, const std::string& address)
    : name_(name), address_(address), shopping_cart_(){}

double Customer::CompletePurchase(Store& market){
  if(shopping_cart_.empty()){
    throw std::runtime_error("Can't complete your purchases. Shopping cart is empty!");
  }
  double amount = 0.0;
  for(const auto& [id, product] : shopping_cart_){
    amount += market.SellProduct(id, product->GetQuantity());
  }
  ClearShoppingCart();
  market.AddIncome(amount);
  return amount;
}

void Customer::AddToCart(const std::string& id, uniquePtr<Product>& product){
  if(product->IsEmpty()){
    throw std::invalid_argument("Try to add an empty product. [id. prod: " + id + "]");
  }
  shopping_cart_.insert(std::make_pair(id, std::move(product)));
}

bool Customer::ClearShoppingCart(){
  if(!shopping_cart_.empty()){
    shopping_cart_.clear();
  }
  if(shopping_cart_.empty()){
    return true;
  }
  return false;
}

void Customer::RemoveProduct(const std::string& id, uint8_t quantity){
  auto product = GetProduct(id);
  if(product == nullptr){
    throw std::invalid_argument("Remove product from shopping cart: " +  id + " not found.");
  }
  if(quantity == 0 || std::max(0, int(product->GetQuantity() - quantity)) == 0){
    shopping_cart_.erase(id);
    return;
  }
  shopping_cart_[id]->SetQuantity(product->GetQuantity() - quantity);
}

bool Customer::IsEmpty() const{
  return name_.empty() && address_.empty() && shopping_cart_.empty();
}

bool Customer::FindProduct(const std::string& id){
  auto search = shopping_cart_.find(id);
  if(search != shopping_cart_.end()){
    return true;
  }
  return false;
}

Product* Customer::GetProduct(const std::string& id){
  if(FindProduct(id)){
    return shopping_cart_[id].get();
  }
  return nullptr;
}

void Customer::Print(std::ostream& out){
  if(this->IsEmpty()){
    throw std::out_of_range("Print client: try to print an empty Customer object.");
  }
  out << "client: " << name_ << ", " << address_ << "\n";
  if(!shopping_cart_.empty()){
    out << "shopping cart:\n";
    for(const auto& item : shopping_cart_){
      out << item.first << ": ";
      item.second->Print(out);
    }
  }
}