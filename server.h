#ifndef SERVER_H
#define SERVER_H

#include <cstdlib>      //exit
#include <netinet/in.h> //htons
#include <arpa/inet.h>  //inet_addr
#include <sys/socket.h> //socket
#include <unistd.h>     //close
#include <iostream>
#include <thread>
#include <QObject>
#include "../info.h"

using namespace std;

class Server : public QObject
{
    Q_OBJECT
public:
    Server();
    void start();
    void socketHandler();

signals:
    void sendMessage(int, int, int);

private:
    struct sockaddr_in endereco;
    int socketId;
    int socketDescriptor;
    Mensagem msg;
    struct sockaddr_in enderecoCliente;
    socklen_t tamanhoEnderecoCliente;
    std::thread t;
};

#endif // SERVER_H
