#ifndef STORE_SIMULATOR_INCLUDE_FILE_WRAPPER_H_
#define STORE_SIMULATOR_INCLUDE_FILE_WRAPPER_H_

#include <cstdio>

class FileHandler{
  public:
    FileHandler();
    FileHandler(const char* path, const char* allowed="a+");
    FileHandler(const FileHandler& other) = delete;
    FileHandler(FileHandler&& other) noexcept;  
    FileHandler& operator=(const FileHandler& other) = delete;
    FileHandler& operator=(FileHandler&& other) noexcept;
    ~FileHandler();
    int EndOfFile() const;
    std::FILE* FileOpen(const char* path, const char* allowed);
    bool IsOpen() const;
    int FileClose();
    std::size_t FileRead(char* buffer, std::size_t counter);
    std::size_t FileWrite(const char* buffer, std::size_t count);
  private:
    std::FILE* stream_;
};
#endif  // STORE_SIMULATOR_INCLUDE_FILE_WRAPPER_H_
