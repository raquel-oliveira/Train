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


/*void socketHandler(int socketId) {
    //Enviar uma msg para o cliente que se conectou
    int bytesenviados;
    bytesenviados = ::send(socketId,msg.data(),msg.size()+1,0);
    if (bytesenviados == -1) {
        printf("Falha ao executar send()");
        exit(EXIT_FAILURE);
    }
    close(socketId);
} */

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
        cout << "> Conectar do servidor" << endl;
    }
    if(selected == 7)
        cout << "> Quit" << endl;
    else
        cout << "  Quit" << endl;
}

int chooseSpeed(Pin play) {
    float v;
    while(true) {
        if(play.getValue())
            return v;
        else {
            v = (readAnalog(PORT_POT) / 4096 * 290) + 10;
            cout << v << endl;
        }
    }
}

void trainMenu(int selected) {
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
            if(selected > 1) {
                selected--;
                trainMenu(selected);
            }
        }
        else if(down.getValue()) {
            if(selected < 7) {
                selected++;
                trainMenu(selected);
            }
        }
        else if(play.getValue())
            return selected - 1;
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
    endereco.sin_addr.s_addr = inet_addr("192.168.0.175");

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
        if(down.getValue()) {
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
        if(play.getValue()) {
            if(selected == 1) {
                if(connected) {
                    connected = false;
                    //close(socketId);
                }
                else {
                    connected = true;
                    /*if ( ::connect (socketId, (struct sockaddr *)&endereco, sizeof(struct sockaddr)) == -1 ) {
                        printf("Falha ao executar connect()\n");
                        exit(EXIT_FAILURE);
                    }*/
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
            }
            else
                quit = true;
        }
        /*bytesenviados = ::send(socketId,&msg,sizeof(msg),0);
        if (bytesenviados == -1) {
            printf("Falha ao executar send()");
            exit(EXIT_FAILURE);
        }*/
    }
    /*while(1) {
        thread t(socketHandler,socketId);
        t.detach();
        usleep(17000);
    } */
    return 0;
}