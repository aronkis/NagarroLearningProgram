#ifndef _GENERAL_STORE_PRINTER_H_
#define _GENERAL_STORE_PRINTER_H_

class Store;
class Client;

class ClientPrinter
{
public:
  virtual void print(const Client* client) const = 0;
};

class ProductPrinter 
{
public:
  virtual void print(const Store* store) const = 0;
};

class Printer : public ClientPrinter, public ProductPrinter
{
public:
  void print(const Client* client) const override;
  void print(const Store* store) const override;
};

#endif