#include "../../include/product/book.h"

#include <exception>

Book::Book(const std::string& name, double price, const std::string& author,
	   uint16_t page_number, uint32_t quantity)
    : Product(name, price, quantity), author_(author), page_number_(page_number){}

void Book::Print(std::ostream& out){
  if(this->IsEmpty()){
    throw std::out_of_range("Print product: try to print an empty Product object.");
  }
  out << name_ << ", price = " << price_ << ", quantity = " << quantity_;
  out << "\n" << "author: " << author_ << "no. of pg.: " << page_number_ << "\n";
}