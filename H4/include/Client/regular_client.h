#ifndef _GENERAL_STORE_REGULAR_CLIENT_H_
#define _GENERAL_STORE_REGULAR_CLIENT_H_

#include "client.h"

class RegularClient : public Client
{
public:
  RegularClient(std::string name, int age, double balance)
    : Client(name, age, balance, 0.10) {}
  double GetTotal() override;

};

#endif
