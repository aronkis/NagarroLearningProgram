#include "./include/server.h"

int main()
{
	Server server(8080);
	server.CreateSocket();
	server.BindServer();
	server.ListenServer();
	server.AcceptClients();
}