#ifndef STORE_SIMULATOR_INCLUDE_PREMIUM_CUSTOMER_H_
#define STORE_SIMULATOR_INCLUDE_PREMIUM_CUSTOMER_H_

#include <ostream>
#include <string>

#include "./customer.h"
#include "../store.h"

class PremiumCustomer: public Customer{
  public:
    PremiumCustomer(const std::string& name, const std::string& address, 
		    double discount = 0.1);
    double CompletePurchase(Store& store) override;
    void Print(std::ostream& out) override;
    void SetDiscount(double discount);
    double GetDicount() const;
  private:
    double discount_;
};
inline void PremiumCustomer::SetDiscount(double discount){
  discount_ = discount;
}
inline double PremiumCustomer::GetDicount() const{
  return discount_;
}
#endif  // STORE_SIMULATOR_INCLUDE_PREMIUM_CUSTOMER_H_
