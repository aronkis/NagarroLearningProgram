#ifndef STORE_SIMULATOR_INCLUDE_UNDERAGE_CUSTOMER_H_
#define STORE_SIMULATOR_INCLUDE_UNDERAGE_CUSTOMER_H_

#include <ostream>
#include <string>

#include "customer.h"
#include "../store.h"
#include "../unique.hpp"

class UnderageCustomer: public Customer{
  public:
    UnderageCustomer(const std::string& name, const std::string& address,
                     uniquePtr<Customer>& guardian, double discount = 0.2);
    double CompletePurchase(Store&) override;
    void Print(std::ostream& out) override;
    void SetDiscount(double discount);
    void SetGuardian(uniquePtr<Customer>& guardian);
    double GetDiscount() const;
    const uniquePtr<Customer>& GetGuardian() const; 
  private:
    double discount_;
    uniquePtr<Customer> guardian_;
};
inline void UnderageCustomer::SetDiscount(double discount){
  discount_ = discount;
}
inline void UnderageCustomer::SetGuardian(uniquePtr<Customer>& guardian){
  guardian_ = std::move(guardian);
}
inline double UnderageCustomer::GetDiscount() const{
  return discount_;
}
inline const uniquePtr<Customer>& UnderageCustomer::GetGuardian() const{
  return guardian_;
}
#endif  // STORE_SIMULATOR_INCLUDE_UNDERAGE_CUSTOMER_H_
