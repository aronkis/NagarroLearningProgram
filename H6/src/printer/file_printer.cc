#include "../../include/printer/file_printer.h"

#include <cstring>
#include <exception>
#include <sstream>
#include <string>

#include "../../include/printer/logger.h"

FilePrinter::FilePrinter(const char* file_path, 
                         const char* writing_mode)
    : file_(file_path, writing_mode){}

void FilePrinter::Print(Printable& printable){
  if(file_.IsOpen()){
    try{
      std::ostringstream out;
      printable.Print(out);  // can throw an exception
      out << "\n";
      std::string temp = out.str();
      const char* buffer = temp.c_str();
      try{
        auto buffer_size = file_.FileWrite(buffer, std::strlen(buffer));
        if(buffer_size != std::strlen(buffer)){
          throw std::runtime_error("error: buffer_size != std::strlen(buffer) when printing in file.");
        }
        file_.FileClose(); // I cannot verify the file if I don't close it first.
      }
      catch(std::runtime_error& e){
        Logger::Log(e.what());
      }
    }
    catch(const std::out_of_range& e ){
      Logger::Log(e.what());
    }
  }
}
