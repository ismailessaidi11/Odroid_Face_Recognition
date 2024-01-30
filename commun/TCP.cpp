/**
 * \file 
 * \brief Fonctions créant la structure de la connection TCP utilisée entre le serveur et le client.

 * \brief Les fonctions de ce fichier établissent les paramètres de connection TCP-IP entre le serveur et le client. La connection est initiée
 * après un appel du client au serveur. Ce dernier, qui était en attente, reçoit l'appel du client, établissant la connection.
 **/

#include "TCP.h"

using namespace std;

/**
 * \int CreateSocket
 * \brief Crée un socket pour les connexions entrantes.
 * \return Le descripteur de socket pour le serveur.
 */

int CreateSocket()                                     // Create a socket for incoming connections
{
    int servSock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP); // Socket descriptor for the server
    if (servSock < 0)
        DieWithSystemMessage("socket() failed");
    return servSock;
}

/** 
 * \struct sockaddr_in ConstructServAddr
 * \brief Construit la structure d'adresse pour le serveur.
 * \param servPort Port du serveur.
 * \param server Booléen indiquant si le côté est un serveur.
 * \param servIP Adresse IP du serveur (si côté client).
 * \return La structure sockaddr_in construite.
 */


struct sockaddr_in ConstructServAddr(in_port_t servPort, bool server, const char *servIP) // Construct the local address structure
{
    // Construct the local address structure
    struct sockaddr_in servAddr;                  // Local address
    memset(&servAddr, 0, sizeof(servAddr));       // Zero out structure
    servAddr.sin_family = AF_INET;                // IPv4 address family
    if (server){
        servAddr.sin_addr.s_addr = htonl(INADDR_ANY); // Any incoming interface
    } else {
        int rtnVal = inet_pton(AF_INET, servIP, &servAddr.sin_addr.s_addr);
        if (rtnVal == 0)
            DieWithUserMessage("inet_pton() failed", "invalid address string");
        else if (rtnVal == -1)
        DieWithSystemMessage("inet_pton() failed");
    }
    servAddr.sin_port = htons(servPort);  

    return servAddr;

}

/**
 * \void BindAndListen
 * \brief Lit et écoute sur le socket.
 * \param servSock Descripteur de socket du serveur.
 * \param servAddr Structure d'adresse à lier.
 * \param MAXPENDING Nombre maximum de connexions en attente.
 */

void BindAndListen(int &servSock, struct sockaddr_in servAddr, const int MAXPENDING)  //think about passing serAddr by reference
{
    // Bind to the local address
    if (bind(servSock, reinterpret_cast<struct sockaddr*>(&servAddr), sizeof(servAddr)) < 0)
        DieWithSystemMessage("bind() failed");

    // Mark the socket so it will listen for incoming connections
    if (listen(servSock, MAXPENDING) < 0)
        DieWithSystemMessage("listen() failed");

}


/**
 * \int get_clntSock
 * \brief Accepte une connexion et récupère le descripteur de socket du client.
 * \param servSock Descripteur de socket du serveur.
 * \return Le descripteur de socket du client accepté.
 */

int get_clntSock(int &servSock)
{
    struct sockaddr_in clntAddr; // Client address
    socklen_t clntAddrLen = sizeof(clntAddr);

    int clntSock = accept(servSock, reinterpret_cast<struct sockaddr*>(&clntAddr), &clntAddrLen);
    if (clntSock < 0)
        DieWithSystemMessage("accept() failed");
        
    //Print Client name
    char clntName[INET_ADDRSTRLEN]; // String to contain client address
    if (inet_ntop(AF_INET, &clntAddr.sin_addr.s_addr, clntName, sizeof(clntName)) != NULL)
        cout << "Handling client " << clntName << "/" << ntohs(clntAddr.sin_port) << endl;
    else
        cout << "Unable to get client address" << endl;
    
    return clntSock;
}

/**
 * \void ConnectToServer
 * \brief Établit une connexion avec un serveur distant.
 * \param sock Descripteur de socket du client.
 * \param servAddr Structure d'adresse du serveur.
 */

void ConnectToServer(int &sock, struct sockaddr_in servAddr)
{

    if (connect(sock, (struct sockaddr *) &servAddr, sizeof(servAddr)) == -1)
        DieWithSystemMessage("connect() failed");    
}

/**
 * \ssize_t safeRecv
 * \brief Reçoit des données du socket de manière sécurisée.
 * \param sock Descripteur de socket.
 * \param buffer Pointeur vers le tampon de réception.
 * \param size Taille du tampon de réception.
 * \param flags Drapeaux pour la fonction recv.
 * \return Le nombre d'octets reçus.
 */

ssize_t safeRecv(int &sock, void* buffer, size_t size, int flags) 
{
    ssize_t numBytes = recv(sock, buffer, size, flags);
    if (numBytes == -1)
        DieWithSystemMessage("recv() failed");
    else if (numBytes == 0)
        DieWithUserMessage("recv()", "connection closed prematurely");
    return numBytes;
}
