#include "./include/client.h"
#include "./include/message.h"

int main()
{
	srand(time(0));
	Client client;
	client.CreateSocket();
	client.ConnectToServer();
	client.SendData(Message("client", "hello from client", "2023-04-2" + std::to_string(rand() % 10)));
}