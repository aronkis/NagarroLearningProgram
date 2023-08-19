#include <arpa/inet.h>
#include <boost/archive/text_oarchive.hpp>
#include "../include/client.h"

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

void Client::SendData(const Message message)
{
  std::stringstream ss;
  boost::archive::text_oarchive oa(ss);
  oa << message;
  std::string serialized_msg = ss.str();

  if (send(socket_info_, serialized_msg.c_str(), serialized_msg.size(), 0) < 0)
  {
    throw std::runtime_error("Error sending message from client");
  }
}