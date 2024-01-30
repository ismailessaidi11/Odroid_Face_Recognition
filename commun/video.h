/**
 * \file 
 * \brief Définition de la classe et la structure comprenant les paramètres vidéo de la caméra.
 * \brief Ce fichier contient la définition de la classe \b Video. Cette dernière contient les informations permettant 
 * au serveur de se connecter à la caméra. Le serveur peut également indiquer la résolution choisie par l'utilisateur et
 * faire une capture d'image. 
 **/

#ifndef VIDEO_H_INCLUDED
#define VIDEO_H_INCLUDED

#include <iostream>
#include <opencv2/opencv.hpp>
#include <time.h>
#include <string>
#include <netinet/in.h>
#include <arpa/inet.h>

using namespace std;
using namespace cv;


/**
 *  \struct Resolution
 *  \brief Définition des paramètres de résolution 
 *  \brief Cette structure contient les paramètres de la résolution de la vidéo. Ces paramètres 
 * sont le nombre d'images  par seconde et la superficie d'une image. 
 * \var x Largeur en pixels.
 * \var Hauteur en pixels.
 * \var fps Images par seconde (FPS).
 **/   
 

struct Resolution{
    int x; /**< Largeur en pixels. */
    int y; /**< Hauteur en pixels. */
    double fps; /**< Images par seconde (FPS). */
};

//Class definition 

/**
 * \class Video
 * \brief Classe gérant les paramètres de la caméra
 * \brief  Cette classe permet d'identifier la caméra par connection USB ainsi que contrôler la 
 * durée, la résolution et la sauvegarde d'une vidéo. 
 **/

class Video
{

    private:
    Resolution res; /**< Résolution de la vidéo. */
    cv::VideoCapture capture; /**< Objet de capture vidéo. */
    int video_duration; /**< Durée de la vidéo en secondes. */
    int Port_ID_cam; /**< Identifiant du port de la caméra. */
    std::string ID_USB_cam; /**< Identifiant USB de la caméra. */

    public:

    /**
     * \brief Constructeur de la classe Video.
     * \param Port_ID_cam Identifiant du port de la caméra.
     * \param video_duration Durée de la vidéo en secondes.
     * \param ID_USB_cam Identifiant USB de la caméra.
     */
        Video(int Port_ID_cam= 0 , int video_duration= 5, string ID_USB_cam= "046d:0825");
        VideoCapture getCapture();
        void setRes(int choice);
        void saveVideo();


        ~Video();
};

//prototype des fonctions
void initFps(Video video);

#endif

