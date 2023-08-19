#include "../include/server.h"
#include <unistd.h>
#include <iostream>
#include <cstring>

Server::~Server()
{
   if (new_socket_ != 0)
   {
    close(new_socket_);
   }
   if (server_info_ != 0)
   {
    close(server_info_);
   }
}

void Server::CreateSocket()
{
  if ((server_info_ = socket(AF_INET, SOCK_STREAM, 0)) < 0)
  {
    perror("ERROR WHILE OPENING THE SOCKET\n");
    exit(EXIT_FAILURE);
  }

  int opt = 1;
  if (setsockopt(server_info_, SOL_SOCKET,
                SO_REUSEADDR | SO_REUSEPORT, 
                &opt, sizeof(opt)))
  {
    perror("ERROR WHILE SETTING THE OPTION!\n");
    exit(EXIT_FAILURE);
  }
}

void Server::BindServer()
{
  server_addr_.sin_family = AF_INET;
  server_addr_.sin_addr.s_addr = INADDR_ANY;
  server_addr_.sin_port = htons(port_);
  if (bind(server_info_, (struct sockaddr *)&server_addr_, sizeof(server_addr_)) < 0)
  {
    perror("ERROR WHILE BIDING!\n");
    exit(EXIT_FAILURE);
  }
}

void Server::ListenServer()
{
  if (listen(server_info_, 3) < 0)
  {
    perror("ERROR WHILE LISTENING!\n");
    exit(EXIT_FAILURE);
  }
}

void Server::AcceptClient()
{
  int server_len = sizeof(server_addr_);
  new_socket_ = accept(server_info_, (struct sockaddr *)&server_addr_, (socklen_t *)&server_len);
  if (new_socket_ < 0)
  {
    perror("ERROR WHILE ACCEPTING A CLIENT!\n");
    exit(EXIT_FAILURE);
  }
}

void Server::ReceiveMessage()
{
  char buffer[1024] = {0};
  if (read(new_socket_, buffer, 1024) < 0)
  {
    perror("ERROR WHILE RECEIVING DATA\n");
    exit(EXIT_FAILURE);
  }
  std::cout << buffer << std::endl;
}

void Server::SendMessage()
{
  const char *message = "This message is from the server!\0";
  if(send(new_socket_, message, strlen(message) + 1, 0) < 0)
  {
    perror("ERROR WHILE SENDING DATA\n");
    exit(EXIT_FAILURE);
  }
}
