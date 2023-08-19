#ifndef _FILE_WRAPPER_FILE_HANDLER_H_
#define _FILE_WRAPPER_FILE_HANDLER_H_

#include <cstdio>

class FileHandler
{
public:
  FileHandler(const char* file_name, const char* mode);
  ~FileHandler();
  FileHandler(const FileHandler&) = delete;
  FileHandler& operator=(const FileHandler&) = delete;
  size_t read(char* buffer, size_t buffer_size);
  void write(const char* buffer, size_t buffer_size);
  bool is_eof() const;
  bool is_open() const;

private:
  FILE* file_;
};

void print(const char* buffer, size_t buffer_size);

#endif