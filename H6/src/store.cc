#include "../include/store.h"

#include <algorithm>
#include <exception>
#include <iostream>
#include <tuple>

#include "../include/printer/logger.h"

Store::Store(const std::string& store_name, const std::string& location, 
	     std::unordered_map<std::string, uniquePtr<Product>>& inventory, double income)
    : income_(income), store_name_(store_name), location_(location), 
      inventory_(std::move(inventory)){}

void Store::AddProduct(uniquePtr<Product>& product, const std::string& id){
  if(product->IsEmpty()){
    throw std::invalid_argument("Try to add an empty product. [id. prod: " + id + "]");
  }
  inventory_.insert(std::make_pair(id, std::move(product)));
}

/**
 * remove product if any (default) [quantity == 0]
 * decrease quantity by 'quantity' units [0 < 'quantity' <= product_quantity]  
 **/
void Store::RemoveProduct(const std::string& id, uint32_t quantity){
  auto product = GetProduct(id);
  if(product == nullptr){
    throw std::invalid_argument("Remove product from store: " +  id + " not found.");
  }
  if(quantity == 0 || std::max(0, int(product->GetQuantity() - quantity)) == 0){
    inventory_.erase(id);
    return;
  }
  product->SetQuantity(product->GetQuantity() - quantity);
}

double Store::SellProduct(const std::string& id, uint32_t quantity){
  try{
    RemoveProduct(id, quantity);
    return inventory_[id]->GetPrice() * quantity;
  }
  catch(std::invalid_argument& e) {
    Logger::Log(e.what());
    return 0.0;
  }
}

void Store::AddIncome(double amount){
  income_ += amount; 
}

/**
 * Succes: 'product_name' and 'quanitty' in stock
 * LessQuantity: 'product_name' in stock but in less quantity
 * NotFount: 'product_name' out of stock
**/
Status Store::AskFor(const std::string& product_name, uint8_t quantity) const{
  for(const auto& item : inventory_){
    if(item.second.get()->GetName() == product_name){
      if(item.second.get()->GetQuantity() < quantity){
        return Status::LessQuantity;
      }
      return Status::Succes;
    }
  }
  return Status::NotFound;
}

bool Store::IsEmpty() const{
  return store_name_.empty() && location_.empty() && income_ == 0.0 && inventory_.empty();
}

bool Store::FindProduct(const std::string& id) const{
  auto search = inventory_.find(id);
  if(search != inventory_.end()){
    return true;
  }
  return false;
}

Product* Store::GetProduct(const std::string& id){
  if(FindProduct(id)){
    return inventory_[id].get();
  }
  return nullptr;
}

void Store::Print(std::ostream& out){
  if(this->IsEmpty()){
    throw std::out_of_range("Print store: try to print an empty Store object.");
  }
  out << "store: " << store_name_ << ", " << location_ << "\n";
  out << "income: " << income_ << "\n";
  for(const auto& item : inventory_){
    out << item.first << ": ";
    item.second.get()->Print(out);
  }
}
