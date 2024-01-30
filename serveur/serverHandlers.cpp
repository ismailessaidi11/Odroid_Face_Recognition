/**
 * \file 
 * \brief Fichier décrivant les fonctions utilisées par le serveur lors de l'utilisation de
 * l'application.

 * \brief Ce fichier contient les définitions des fonctions de contrôle de la caméra, de la capture d'images
 * et de leur traitement avant leur envoi vers le client. Les fonctions de réception des demandes du client sont
 * également définies dans ce fichier.
 **/

#include "serverHandlers.h"

using namespace std;

/**
 * \void HandleClient(int &clntSocket, uint32_t &messages, Video &video,string &format)
 * \brief Fonction permettant au serveur de gérer les demandes du client. Le serveur peut ainsi capturer une image,
 * la compresser, l'envoyer au client et, si nécessaire, modifier les paramètres de la caméra en fonction de la 
 * demande du client.
 * \param clntSocket Le socket du client.
 * \param messages Les données de message.
 * \param video L'objet Video utilisé pour capturer les images.
 * \param format Le format d'image utilisé pour la compression.
 **/

void HandleClient(int &clntSocket, uint32_t &messages, Video &video,string &format)
{
    
    Mat frame;
    video.getCapture() >> frame;
    if (frame.empty()) {
        cout << "Failed to capture an image" << endl;
        exit(0);
    }
    // Compressing image
    size_t expectedImageSize = 152064;
    vector<uchar> compressedImageBuffer(expectedImageSize);
    imencode(format, frame, compressedImageBuffer);
    int image_size = compressedImageBuffer.size();


    // Send image
    send(clntSocket, &image_size, sizeof(image_size), 0);
    send(clntSocket, compressedImageBuffer.data(), image_size, 0);

    // Receive messages
    ssize_t recv_value = safeRecv(clntSocket, &messages, sizeof(messages), 0);
    if (messages & ISCHANGED){
        update_camera(messages, video, format);
    }
}

/**
 * \void update_camera(uint32_t &messages, Video &video, string &format) 
 * \brief Reçoit les messages du client et met à jour les paramètres de la caméra en fonction des 
 * demandes du client.
 * 
 * \param messages Les données de message.
 * \param video L'objet Video utilisé pour les mises à jour de la caméra.
 * \param format Le format d'image à mettre à jour.
 */

void update_camera(uint32_t &messages, Video &video, string &format)
{
    int choice;
    //check resolution
    switch(messages & RESMSK){
        case 0x00000000:
            choice=2;           //(320x176)
            video.setRes(choice);
            break;
        case 0x00000002: 
            choice=3;           //(320x240)
            video.setRes(choice);
            break;
        case 0x00000004:
            choice=4;           //(352x288)
            video.setRes(choice);
            break;
        case 0x00000006:
            choice=5;            //(432x240)
            video.setRes(choice);
            break;
    }
    
    //handle format change
    if((messages & FORMATMSK)!= 0){
        format=".png";
    }else{
        format=".jpeg";
    }
    messages &= DONE_CHANGING;
    
}

/**
 * \void Read_and_update_message(uint32_t &messages, Odroid odroid, int &clntSock, bool &image_down, bool &button_was_pressed)  
 * \brief Le serveur lit les données reçues concernant la lumière et lebouton reliés à l'Odroid-C2 et il met à jour les messages
 * qu'il envoie ensuite au client.

 * \param messages Les données du message.
 * \param odroid L'objet Odroid pour la lecture des informations.
 * \param clntSock Le socket du client.
 * \param image_down Indique si une image a été reçue.
 * \param button_was_pressed Indique si le bouton a été enfoncé.
 */

void Read_and_update_message(uint32_t &messages, Odroid odroid, int &clntSock, bool &image_down, bool &button_was_pressed)
{
     //light 
    if (odroid.no_light())
    {
        messages|=NO_LIGHT;
    } else{
        messages&=LIGHT;
    }
    //button
    if (odroid.button_pressed() && (button_was_pressed==false))
    {
        messages|=BUTTON_PRESSED;
        send(clntSock, &messages, sizeof(messages), 0);
        button_was_pressed = true;               //debouncing

    } else if (!(odroid.button_pressed()) && (button_was_pressed==true)){
        messages&=BUTTON_NOT_PRESSED;
        send(clntSock, &messages, sizeof(messages), 0);
        button_was_pressed = false;             //debouncing

    } else {
        messages &=BUTTON_NOT_PRESSED;
        send(clntSock, &messages, sizeof(messages), 0);
    }

    if((messages & LIGHTMSK )!= 0)
    {
        image_down = true;
    } else {
        image_down = false;
    } 
}