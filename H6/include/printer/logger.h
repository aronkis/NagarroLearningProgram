#ifndef STORE_SIMULATION_INCLUDE_LOGGER_H_
#define STORE_SIMULATION_INCLUDE_LOGGER_H_

#include <iostream>
#include <cstring>
#include <exception>
#include <sstream>
#include <string>

#include "./file_handler.h"

class Logger{
  public:
    template<class... exception_values> static void Log(const exception_values&... value);
  private:
    static FileHandler log_;
};

template<class... exception_values>
void Logger::Log(const exception_values&... value){
  std::ostringstream out;
  (out << ... << value) << "\n";
  std::string temp = out.str();
  const char* buffer = temp.c_str();
  try{
    auto buffer_size = log_.FileWrite(buffer, std::strlen(buffer));
    if(buffer_size != std::strlen(buffer)){
      throw std::runtime_error("error: buffer_size != std::strlen(buffer) when printing in file.");
    }
  }
  catch(std::runtime_error& e){
    std::cout << "error: Can't write in log file. " << e.what() << "\n"; 
  }
}
#endif  // STORE_SIMULATION_INCLUDE_LOGGER_H_