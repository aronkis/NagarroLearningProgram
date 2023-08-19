#ifndef STORE_SIMULATOR_INCLUDE_PRINTER_CONSOLE_PRINTER_H_
#define STORE_SIMULATOR_INCLUDE_PRINTER_CONSOLE_PRINTER_H_

#include <exception>
#include <iostream>

#include "./logger.h"
#include "./printable.h"
#include "./printer.h"

class ConsolePrinter: public Printer{
  public:
    void Print(Printable& printable) override {
      try{
        printable.Print(std::cout); // can throw an exception
        std::cout << std::endl;
      }
      catch (const std::out_of_range& e){
        Logger::Log(e.what());
      }
    };
};
#endif  // STORE_SIMULATOR_INCLUDE_PRINTER_CONSOLE_PRINTER_H_