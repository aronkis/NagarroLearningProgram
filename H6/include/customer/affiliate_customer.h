#ifndef STORE_SIMULATOR_INCLUDE_AFFILIATE_CUSTOMER_H_
#define STORE_SIMULATOR_INCLUDE_AFFILIATE_CUSTOMER_H_

#include <ostream>
#include <cstdint>
#include <string>

#include "customer.h"
#include "../store.h"

class AffiliateCustomer: public Customer{
  public:
    AffiliateCustomer(const std::string& name, const std::string& address, 
		      uint32_t points = 10);
    double CompletePurchase(Store& store) override;
    void Print(std::ostream& out) override;
    void SetPoints(uint32_t points);
    uint32_t GetPoints() const;
  private:
    uint32_t points_;
};
inline void AffiliateCustomer::SetPoints(uint32_t points){
  points_ = points;
}
inline uint32_t AffiliateCustomer::GetPoints() const{
  return points_;
}
#endif  // STORE_SIMULATOR_INCLUDE_AFFILIATE_CUSTOMER_H_
