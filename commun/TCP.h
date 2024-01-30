/**
 * \file 
 * \brief Déclaration des fonctions utilisées pour la connection TCP-IP entre le serveur et le client.
  
 * \brief Les fonctions permettant de créer, puis d'établir la communication TCP-IP entre le serveur et le client sont déclarées 
 * dans ce fichier Les bibliothèques utilisées sont indiquées.
 **/

#include <iostream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdint.h>
#include "message.h"

int CreateSocket();     // Create a socket for incoming connections
struct sockaddr_in ConstructServAddr(in_port_t servPort, bool server,const char *servIP); // Construct the local address structure
void BindAndListen(int &servSock, struct sockaddr_in servAddr, const int MAXPENDING);  //think about passing serAddr by reference
int get_clntSock(int &servSock);
void ConnectToServer(int &sock, struct sockaddr_in servAddr);
ssize_t safeRecv(int &sock, void* buffer, size_t size, int flags);