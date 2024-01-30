/**
 * \file
 * \brief Fichier gérant l'utilisation des fonctions, macros et variables dans les fichiers du dossier \b client .  
 
 * \brief Fichier gérant les fonctions définies dans les dossiers \b client et \b commun selon 
 * des directives données par l'utilisateur. Ce dernier peut choisir les paramètres de résolution de la caméra,
 * choisir un mode de reconnaissance faciale, recevoir une photo et la nommer. Les paramètres de communication
 * avec l'Odroid-C2 sont également définis dans ce fichier.
 **/ 
 
#include "handlers.h"



using namespace std;
using namespace cv;

/**
 * \int main(int argc, char *argv[]) 
 * \brief Fonction gérant le programme du côté client. Elle initialise les variables, établi et gère une connexion TCP
 * avec le serveur, traite des images et indique le statut de l'exécution du programme. Elle effectue ces opérations
 * jusqu'à la fin du pogramme.
 * 
 * \param argc Nombre d'arguments de commande.
 * \param argv Tableau d'arguments de commande.
 * \return Valeur de retour indiquant le statut de l'exécution du programme.
 */

int main(int argc, char *argv[]) 
{
    bool image_down(false);
    bool push_button(false);
    uint32_t messages = DEFAULT;    // 
    int image_ID = 0;

    const char *servIP = SERVER_IP; // server IP address 
    in_port_t servPort = PortAddr; // server port (numeric).

    int sock = CreateSocket();

    struct sockaddr_in servAddr = ConstructServAddr(servPort, false, servIP); // Server address

    ConnectToServer(sock,servAddr);

    //create directory to store images 
    string data_base_path = "./data_base";    
    system(("mkdir -p " + data_base_path).c_str());
   
    while (true) {
        handle_odroid_message(sock, messages, image_down, push_button);
        while(!(image_down))
        {
            if (push_button){ 
                show_and_save_image(image_ID, push_button,sock, messages, data_base_path);
            } else {
                stream_image(sock, messages);
            }
            handle_odroid_message(sock, messages, image_down, push_button);
        }
        // show black image if no light 
        Mat blackImage = Mat::zeros(Size(352, 288), CV_8UC3);
        imshow("ImageWindow", blackImage);
        KeyHandling(sock, messages);
    }

    return 0;
}
