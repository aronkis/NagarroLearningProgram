#ifndef STORE_SIMULATOR_INCLUDE_PRINTER_FILE_PRINTER_H_
#define STORE_SIMULATOR_INCLUDE_PRINTER_FILE_PRINTER_H_

#include "file_handler.h"
#include "printable.h"
#include "printer.h"
#include <iostream>

class FilePrinter: public Printer{
  public:
    FilePrinter(const char* file_path, const char* writing_mode = "a+");
    ~FilePrinter(){
      std::cout << "~FilePrinter()\n";
    }
    void Print(Printable& printable) override;
    void SetFileHandler(FileHandler&& file_handler);
    FileHandler& GetFileHandler();
  private:
    FileHandler file_;
};
inline void FilePrinter::SetFileHandler(FileHandler&& file_handler){
  file_ = std::move(file_handler);
}
inline FileHandler& FilePrinter::GetFileHandler(){
  return file_;
}
#endif  // STORE_SIMULATOR_INCLUDE_PRINTER_FILE_PRINTER_H_
