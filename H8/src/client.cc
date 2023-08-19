#include "../include/client.h"
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <iostream>

void Client::CreateSocket()
{
  socket_info_ = socket(AF_INET, SOCK_STREAM, 0);

  if (socket_info_ < 0)
  {
    perror("ERROR WHILE OPENING THE SOCKET\n");
    exit(EXIT_FAILURE);
  }

  server_addr_.sin_family = AF_INET;
  server_addr_.sin_port = htons(8080);

  if (inet_pton(AF_INET, "127.0.0.1", &server_addr_.sin_addr) <= 0)
  {
    perror("INET_PTON FAILED!\n");
    exit(EXIT_FAILURE);
  }
}

void Client::ConnectToServer()
{
  if (connect(socket_info_, (struct sockaddr*)& server_addr_, sizeof(server_addr_)) < 0)
  {
    perror("ERROR WHILE CONNECTING!\n");
    exit(EXIT_FAILURE);
  }
}

void Client::SendData(const char* buffer, int buffer_size)
{
    if (send(socket_info_, buffer, buffer_size, 0) < 0)
    {
      perror("ERROR WHILE SENDING DATA\n");
      exit(EXIT_FAILURE);
    }
}

void Client::ReceiveData(char* buffer, int buffer_size)
{
    int val = read(socket_info_, buffer, buffer_size);
    if (val < 0)
    {
      perror("ERROR WHILE RECEIVING DATA\n");
      exit(EXIT_FAILURE);
    }
    std::cout << buffer << std::endl;
}
