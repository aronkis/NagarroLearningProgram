#ifndef STORE_SIMULATOR_INCLUDE_PRINTER_PRINTABLE_H_
#define STORE_SIMULATOR_INCLUDE_PRINTER_PRINTABLE_H_

#include <ostream>

class Printable{
  public:
    virtual void Print(std::ostream& out) = 0;
};
#endif  // STORE_SIMULATOR_INCLUDE_PRINTER_PRINTABLE_H_
