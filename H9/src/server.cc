#include <sstream>
#include <../../boost/serialization/string.hpp>
#include <../../boost/archive/text_iarchive.hpp>
#include "../include/server.h"
#include "../include/message.h"

std::ofstream Server::log_("../logs.txt", std::fstream::out | std::fstream::app);

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
  if (listen(server_info_, 5) < 0)
  {
    perror("ERROR WHILE LISTENING!\n");
    exit(EXIT_FAILURE);
  }
}

void Server::HandleClient(int socket)
{
  char buffer[1024];

  int bytes_received = read(socket, buffer, sizeof(buffer));
  if (bytes_received < 0)
  {
    perror("ERROR WHILE HANDLING A CLIENT!\n");
    exit(EXIT_FAILURE);
  }

  std::string serialized_msg(buffer, bytes_received);
  Message message;
  std::stringstream ss(serialized_msg);
  boost::archive::text_iarchive ia(ss);
  ia >> message;

  log_ << message.getSender() << " " << message.getDate() << std::endl;

  close(socket);
}

void Server::AcceptClients()
{
  while (true)
  {
    int server_len = sizeof(server_addr_);
    new_socket_ = accept(server_info_, (struct sockaddr *)&server_addr_, (socklen_t *)&server_len);

    if (new_socket_ < 0)
    {
      perror("ERROR WHILE ACCEPTING A CLIENT!\n");
      exit(EXIT_FAILURE);
    }
    clients_.emplace_back(std::thread(Server::HandleClient, new_socket_));
  }
}