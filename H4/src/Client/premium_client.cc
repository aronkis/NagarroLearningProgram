#include "../include/Client/premium_client.h"
#include "../include/Product/Drink/alcoholic.h"

double PremiumClient::GetTotal()
{
  double total = 0.0;
  for (auto& prod : cart_)
  {
    total += prod.first->GetPrice() * prod.second;
  }
  return total - (total * discount_);
}