#include <cstdio>       //printf
#include <cstring>      //memset
#include <cstdlib>      //exit
#include <netinet/in.h> //htons
#include <arpa/inet.h>  //inet_addr
#include <sys/socket.h> //socket
#include <unistd.h>     //close
#include <thread>
#include <pthread.h>
#include <vector>
#include <iostream>
#include "../Utils/api_gpio/pmap.h"
#include "../Utils/api_gpio/pin.h"
#include "../Utils/utils.h"
#include <string>

using namespace std;

#define PORTNUM 4325
#define PORT_POT 1 //potentiometer

class Mensagem {
    public:
        vector<bool> trainStatus;
        vector<int> trainSpeeds;
        Mensagem() : trainStatus(7), trainSpeeds(7) {}
};

void mainMenu(int selected, bool connected) {
    system("clear");
    if(connected) {
        if(selected == 1)
            cout << "> Desconectar do servidor" << endl;
        else
            cout << "  Desconectar do servidor" << endl;
        if(selected == 2)
            cout << "> Ligar todos os trens" << endl;
        else
            cout << "  Ligar todos os trens" << endl;
        if(selected == 3)
            cout << "> Desligar todos os trens" << endl;
        else
            cout << "  Desligar todos os trens" << endl;
        if(selected == 4)
            cout << "> Ligar um trem específico" << endl;
        else
            cout << "  Ligar um trem específico" << endl;
        if(selected == 5)
            cout << "> Desligar um trem específico" << endl;
        else
            cout << "  Desligar um trem específico" << endl;
        if(selected == 6)
            cout << "> Alterar a velocidade de um trem específico" << endl;
        else
            cout << "  Alterar a velocidade de um trem específico" << endl;
    }
    else {
        if(selected == 1)
            cout << "> Conectar ao servidor" << endl;
        else
            cout << "  Conectar ao servidor" << endl;
    }
    if(selected == 7)
        cout << "> Quit" << endl;
    else
        cout << "  Quit" << endl;
}

int chooseSpeed(Pin play) {
    float v;
    int pot;
    while(true) {
        if(play.getValue()) {
            usleep(200000);
            return v;
        }
        else {
            usleep(200000);
            pot = readAnalog(PORT_POT);
            v = (pot / 4096.0 * 290) + 10;
            system("clear");
            cout << v << endl;
        }
    }
}

void trainMenu(int selected) {
    system("clear");
    if(selected == 1)
        cout << "> 1" << endl;
    else
        cout << "  1" << endl;
    if(selected == 2)
        cout << "> 2" << endl;
    else
        cout << "  2" << endl;
    if(selected == 3)
        cout << "> 3" << endl;
    else
        cout << "  3" << endl;
    if(selected == 4)
        cout << "> 4" << endl;
    else
        cout << "  4" << endl;
    if(selected == 5)
        cout << "> 5" << endl;
    else
        cout << "  5" << endl;
    if(selected == 6)
        cout << "> 6" << endl;
    else
        cout << "  6" << endl;
    if(selected == 7)
        cout << "> 7" << endl;
    else
        cout << "  7" << endl;
}

int chooseTrain(Pin up, Pin down, Pin play) {
    int selected = 1;
    trainMenu(selected);
    while(true){
        if(up.getValue()) {
            usleep(200000);
            if(selected > 1) {
                selected--;
                trainMenu(selected);
            }
        }
        else if(down.getValue()) {
            usleep(200000);
            if(selected < 7) {
                selected++;
                trainMenu(selected);
            }
        }
        else if(play.getValue()) {
            usleep(200000);
            return selected - 1;
        }

    }
}

int main(int argc, char *argv[]) {
    struct sockaddr_in endereco;
    int socketId;

    init();
    Pin up ("P9_27", Direction::IN, Value::LOW);
    Pin down ("P9_41", Direction::IN, Value::LOW);
    Pin play ("P9_42", Direction::IN, Value::LOW);

    //Configurações do endereço
    memset(&endereco, 0, sizeof(endereco));
    endereco.sin_family = AF_INET;
    endereco.sin_port = htons(PORTNUM);
    endereco.sin_addr.s_addr = inet_addr("127.0.0.1");

    socketId = ::socket(AF_INET, SOCK_STREAM, 0);

    Mensagem msg;
    for(int i = 0; i < 7; i++) {
        msg.trainStatus[i] = false;
        msg.trainSpeeds[i] = 100;
    }
    int bytesenviados;

    //Verificar erros
    if (socketId == -1) {
        printf("Falha ao executar socket()\n");
        exit(EXIT_FAILURE);
    }

    int selected = 1;
    bool connected = false;
    bool quit = false;
    mainMenu(selected, connected);
    while(!quit){
        if(up.getValue()) {
            usleep(200000);
            if(connected) {
                if(selected > 1) {
                    selected--;
                    mainMenu(selected, connected);
                }
            }
            else {
                if(selected == 7) {
                    selected = 1;
                    mainMenu(selected, connected);
                }
            }
        }
        else if(down.getValue()) {
            usleep(200000);
            if(connected) {
                if(selected < 7) {
                    selected++;
                    mainMenu(selected, connected);
                }
            }
            else {
                if(selected == 1) {
                    selected = 7;
                    mainMenu(selected, connected);
                }
            }
        }
        else if(play.getValue()) {
            usleep(200000);
            if(selected == 1) {
                if(connected) {
                    connected = false;
                    close(socketId);
                }
                else {
                    connected = true;
                    if ( ::connect (socketId, (struct sockaddr *)&endereco, sizeof(struct sockaddr)) == -1 ) {
                        printf("Falha ao executar connect()\n");
                        exit(EXIT_FAILURE);
                    }
                }
                mainMenu(selected, connected);
            }
            else if(selected == 2) {
                for(int i = 0; i < 7; i++)
                    msg.trainStatus[i] = true;
            }
            else if(selected == 3) {
                for(int i = 0; i < 7; i++)
                    msg.trainStatus[i] = false;
            }
            else if(selected == 4) {
                int t = chooseTrain(up, down, play);
                msg.trainStatus[t] = true;
                mainMenu(selected, connected);
            }
            else if(selected == 5) {
                int t = chooseTrain(up, down, play);
                msg.trainStatus[t] = false;
                mainMenu(selected, connected);
            }
            else if(selected == 6) {
                int t = chooseTrain(up, down, play);
                int v = chooseSpeed(play);
                msg.trainSpeeds[t] = v;
                mainMenu(selected, connected);
            }
            else
                quit = true;
        }
        if(connected) {
          bytesenviados = ::send(socketId,&msg,sizeof(msg),0);
          if (bytesenviados == -1) {
            printf("Falha ao executar send()");
            exit(EXIT_FAILURE);
          }
        }
    }
    return 0;
}
