#include "server.h"

Server::Server()
{
    socklen_t tamanhoEnderecoCliente = sizeof(struct sockaddr);
    memset(&endereco, 0, sizeof(endereco));
        endereco.sin_family = AF_INET;
        endereco.sin_port = htons(PORTNUM);
        endereco.sin_addr.s_addr = inet_addr(IP);
        socketId = socket(AF_INET, SOCK_STREAM, 0);
        //Verificar erros
        if (socketId == -1) {
            printf("Falha ao executar socket()\n");
            exit(EXIT_FAILURE);
        }
        //Conectando o socket a uma porta. Executado apenas no lado servidor
        if (::bind(socketId, (struct sockaddr *)&endereco, sizeof(struct sockaddr)) == -1 ) {
            printf("Falha ao executar bind()\n");
            exit(EXIT_FAILURE);
        }

        //Habilitando o servidor a receber conexoes do cliente
        if ( ::listen( socketId, 10 ) == -1) {
            printf("Falha ao executar listen()\n");
            exit(EXIT_FAILURE);
        }
}

void Server::start() {

        //disparar a thread
        t = std::thread(&Server::socketHandler,this);
        t.detach();
}

void Server::socketHandler() {
    int byteslidos;

    while(1) {
        //Servidor fica bloqueado esperando uma conexão do cliente
        socketDescriptor = ::accept( socketId,(struct sockaddr *) &enderecoCliente,&tamanhoEnderecoCliente );
        cout << "Cliente conectado" << endl;
        //Verificando erros
        if ( socketDescriptor == -1) {
            printf("Falha ao executar accept()");
            exit(EXIT_FAILURE);
        }

        byteslidos = 1;
        while(byteslidos != 0) {

            //receber uma msg do cliente
            byteslidos = recv(socketDescriptor,&msg,sizeof(msg),0);
            if (byteslidos == -1) {
                printf("Falha ao executar recv()");
                exit(EXIT_FAILURE);
            }
            else if(byteslidos == 0)
                break;
            emit sendMessage(msg.command, msg.train, msg.speed);
        }
        close(socketDescriptor);
    }
}
