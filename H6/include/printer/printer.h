#ifndef STORE_SIMULATOR_INCLUDE_PRINTER_PRINTER_H_
#define STORE_SIMULATOR_INCLUDE_PRINTER_PRINTER_H_

#include "./printable.h"

class Printer{
  public:
    virtual void Print(Printable& printable) = 0;
};
#endif  // STORE_SIMULATOR_INCLUDE_PRINTER_H_