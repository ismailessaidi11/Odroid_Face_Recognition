/**
 * \file 
 * \brief Déclarations et définitions des bibliotèques, fonctions et variables globales utilisées dans le dossier \b client .
 
 * \brief Ce fichier contient les déclarations des variables globales des fichiers du dossier \b client , 
 * la liste des bibliothèques et headers inclus dans les fichiers,
 * la déclaration d'utilisation du namespace \b cv   
 * et les déclarations des fonctions définies dans les fichiers du dossier \b client . 
 **/

/**
* \file handlers.cpp
**/
#ifndef HANDLERS_H_INCLUDED
#define HANDLERS_H_INCLUDED

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <cstdio>
#include <cstring>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <vector>
#include <dirent.h>
#include <sys/stat.h>
#include <opencv2/opencv.hpp>
#include "../commun/video.h"
#include "../commun/TCP.h"
#include "../commun/message.h"
#include "../commun/definitions.h"


using namespace cv;

Mat DecompressImage(vector<uchar> &compressedImageBuffer );
void KeyHandling(int &sock, uint32_t &messages);
Mat receive_image( int &sock);
void stream_image(int &sock, uint32_t &messages);
void save_image(int &sock, int image_ID);
void handle_odroid_message(int &sock, uint32_t &messages, bool &image_down, bool &push_button);
void show_and_save_image(int &image_ID, bool push_button,int &sock, uint32_t &messages, const string &data_base_path);
void detect_and_save_faces( Mat& image, int &image_ID, const string &data_base_path);

#endif