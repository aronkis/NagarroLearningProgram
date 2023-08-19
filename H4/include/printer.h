#ifndef _GENERAL_STORE_PRINTER_H_
#define _GENERAL_STORE_PRINTER_H_

#include <memory>

class Store;
class Product;
class Client;

class ClientPrinter
{
public:
  virtual void print(const std::shared_ptr<Client> client) const = 0;
};

class ProductPrinter 
{
public:
  virtual void print(const std::shared_ptr<Store> store) const = 0;
};

class Printer : public ClientPrinter, public ProductPrinter
{
public:
  void print(const std::shared_ptr<Client> client) const override;
  void print(const std::shared_ptr<Store> store) const override;
};

#endif