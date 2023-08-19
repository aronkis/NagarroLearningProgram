#ifndef _GENERAL_STORE_PREMIUM_CLIENT_H_
#define _GENERAL_STORE_PREMIUM_CLIENT_H_

#include "client.h"

class PremiumClient : public Client
{
public:
  PremiumClient(std::string name, int age, double balance)
    : Client(name, age, balance, 0.25) {}
};

#endif
