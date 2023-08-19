#ifndef _CLIENTSERVER_SERVER_H_
#define _CLIENTSERVER_SERVER_H_

#include <netinet/in.h>

class Server
{
public:
    Server(int port)
      : port_(port) {}
    ~Server();
    void CreateSocket();
    void BindServer();
    void ListenServer();
    void AcceptClient();
    void ReceiveMessage();
    void SendMessage();

private:
    int port_ = 0;
    int server_info_ = 0, new_socket_ = 0;
    struct sockaddr_in server_addr_;
};

#endif