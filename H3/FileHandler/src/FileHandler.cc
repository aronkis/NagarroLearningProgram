#include "FileHandler.h"

#include <iostream>

FileHandler::FileHandler(const char* file_name, const char* mode)
{
  file_ = fopen(file_name, mode);
  if (!file_)
  {
    std::cout << "Failed to open file!\n";
  }
}

FileHandler::~FileHandler()
{
  fclose(file_);
}

size_t FileHandler::read(char* buffer, size_t buffer_size)
{
  size_t count = fread(buffer, sizeof(char), buffer_size, file_);
  
  if (count != buffer_size && ferror(file_))
  {
    std::cout << "Failed to read from file!";
  }

  return count;
}

void FileHandler::write(const char* buffer, size_t buffer_size)
{
  size_t count = fwrite(buffer, sizeof(char), buffer_size, file_);

  if (count != buffer_size)
  {
    std::cout << "Failed to write to file";
  }
}

bool FileHandler::is_eof() const 
{
  return feof(file_);
}

bool FileHandler::is_open() const
{
  return file_ != NULL ? 1 : 0;
}

void print(const char* buffer, size_t buffer_size)
{
  for (int i = 0; i < buffer_size; i++)
  {
    std::cout << buffer[i];
  }
}