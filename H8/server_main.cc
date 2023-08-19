#include "./include/server.h"

int main()
{
    Server server(8080);
    server.CreateSocket();
    server.BindServer();
    server.ListenServer();
    server.AcceptClient();
    server.ReceiveMessage();
    server.SendMessage();

    return 0;
}