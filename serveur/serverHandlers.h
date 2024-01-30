/**
 * \file 
 * \brief Déclarations et définitions des bibliotèques, fonctions et variables globales utilisées dans le dossier \b serveur .
 
 * \brief Ce fichier contient les déclarations des variables globales des fichiers du dossier \b serveur , 
 * la liste des bibliothèques et headers inclus dans les fichiers,
 * la déclaration d'utilisation du namespace \b cv   
 * et les déclarations des fonctions définies dans les fichiers du dossier \b serveur . 
 **/
#ifndef SERVER_HANDLERS_H_INCLUDED
#define SERVER_HANDLERS_H_INCLUDED

#include <iostream>
#include <string>
#include <cstring>
#include <cstdlib>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdint.h>
#include "../commun/video.h"
#include "../commun/message.h"
#include "../commun/TCP.h"
#include "../commun/definitions.h"
#include "odroid.h"

using namespace cv;

void HandleClient(int &clntSocket, uint32_t &messages, Video &video, string &format);
void update_camera(uint32_t &messages, Video &video, string &format);
void Read_and_update_message(uint32_t &messages, Odroid odroid, int &clntSock, bool &image_down, bool &button_was_pressed);

#endif