#include "../../include/printer/file_handler.h"

#include <stdexcept>
#include <utility>

#include <unistd.h>
#include <fcntl.h>

FileHandler::FileHandler(): stream_(nullptr){}

FileHandler::FileHandler(const char* path, const char* allowed){
  stream_ = FileOpen(path, allowed);
}

FileHandler::FileHandler(FileHandler&& other) noexcept
    : stream_(std::move(other.stream_)){}

FileHandler& FileHandler::operator=(FileHandler&& other) noexcept{
  if(this != &other){
    stream_ = std::move(other.stream_);
  }
  return *this;
}

FileHandler::~FileHandler(){
  if(IsOpen()){
    FileClose();
  }
}

int FileHandler::EndOfFile() const {
  return std::feof(stream_);
}

std::FILE* FileHandler::FileOpen(const char* path, const char* allowed) {
  return std::fopen(path, allowed);  // open file in 'allowed' mode
}

bool FileHandler::IsOpen() const{
  return stream_ != nullptr;
}

int FileHandler::FileClose(){
  int output = std::fclose(stream_);
  stream_ = nullptr;
  return output;
}

std::size_t FileHandler::FileRead(char* buffer,std::size_t counter){
  int file_descriptor = fileno(stream_);
  int access_mode = fcntl(file_descriptor, F_GETFL) & O_ACCMODE;
  if(access_mode != O_RDONLY && access_mode != O_RDWR){
    throw std::runtime_error("File isn't open in read mode.");
  }
  return std::fread(buffer, sizeof(char), counter, stream_);
}

std::size_t FileHandler::FileWrite(const char* buffer, std::size_t count){
  int file_descriptor = fileno(stream_);
  int access_mode = fcntl(file_descriptor, F_GETFL) & O_ACCMODE;
  if(access_mode != O_WRONLY && access_mode != O_RDWR){
    throw std::runtime_error("File isn't open in write mode.");
  }
  return std::fwrite(buffer, sizeof(char), count, stream_);
}
