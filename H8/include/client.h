#ifndef _CLIENTSERVER_CLIENT_H_
#define _CLIENTSERVER_CLIENT_H_

#include <netinet/in.h>

class Client
{
public:
  void CreateSocket();
  void ConnectToServer();
  void SendData(const char* buffer, int buffer_size);
  void ReceiveData(char* buffer, int buffer_size);
  
private:
  int socket_info_ = 0;
  struct sockaddr_in server_addr_;
};

#endif
