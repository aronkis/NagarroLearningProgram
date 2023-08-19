#include <cstdlib>
#include "FileHandler.h"

void writeFile()
{
  FileHandler file("../files/log.txt", "w");
  char* buffer = "Nothing to worry about!\n";
  file.write(buffer, 24);
}

void readFile()
{
  FileHandler file("../files/list.txt", "r");
  size_t buffer_size  = 10;
  char* buffer = (char*)malloc(buffer_size);
  file.read(buffer, buffer_size);
  print(buffer, buffer_size);
}

int main()
{
  readFile();
  writeFile(); 
  return 0;
}