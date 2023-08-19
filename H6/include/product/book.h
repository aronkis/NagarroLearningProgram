#ifndef STORE_SIMULATOR_INCLUDE_PRODUCT_BOOK_H_
#define STORE_SIMULATOR_INCLUDE_PRODUCT_BOOK_H_

#include <ostream>
#include <cstdint>
#include <string>

#include "product.h"

class Book: public Product{
  public:
    Book(const std::string& name, double price, const std::string& author, 
         uint16_t page_number, uint32_t quantity);
    void Print(std::ostream& out) override;
    void SetAuthor(const std::string& author);
    void SetPageNumber(uint16_t page_number);
    const std::string& GetAuthor() const;
    uint16_t GetPageNumber() const;
  private:
    std::string author_;
    uint16_t page_number_;
};
inline void Book::SetAuthor(const std::string& author){
  author_ = author;
}
inline void Book::SetPageNumber(uint16_t page_number){
  page_number_ = page_number;
}
inline const std::string& Book::GetAuthor() const{
  return author_;
}
inline uint16_t Book::GetPageNumber() const{
  return page_number_;
}
#endif  // STORE_SIMULATOR_INCLUDE_PRODUCT_BOOK_H_
