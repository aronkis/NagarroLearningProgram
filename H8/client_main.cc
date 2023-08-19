#include "./include/client.h"

int main()
{
    Client client;
    client.CreateSocket();
    client.ConnectToServer();
    client.SendData("This message is from the client!", 33);
    char buffer[50];
    client.ReceiveData(buffer, 50);

    return 0;
}