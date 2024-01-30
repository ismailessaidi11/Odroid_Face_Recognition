/**
 * \file
 * \brief Fichier gérant l'utilisation des fonctions, macros et variables dans les fichiers du dossier \b serveur .  

 * \brief Fichier gérant les fonctions définies dans les dossiers \b serveur et \b commun selon 
 * les demandes de capture d'image reçues. Les demandes proviennent du client qui décide à partir de son disque des
 * paramètres de capture d'image que le serveur va utiliser. Le serveur gère la réception des demandes, le contrôle de la caméra,
 * les captures d'images et l'envoi de celles-ci au client.Les paramètres de communication
 * avec le client sont également définis dans ce fichier
 **/

#include "../commun/video.h"
#include "serverHandlers.h"
#include "odroid.h"


using namespace std;
/**
 * \int main(int argc, char *argv[]) 
 * \brief Fonction gérant le programme du côté serveur. Elle initialise les variables, établi et gère une connexion TCP
 * avec le client, contrôler la caméra et les captures d'images. Elle lit également les signaux provenant des composantes
 * reliées à l'Odroid-C2 et indique le statut de l'exécution du programme. Elle effectue ces opérations
 * jusqu'à la fin du pogramme.
 * 
 * \param argc Nombre d'arguments de commande.
 * \param argv Tableau d'arguments de commande.
 * \return Valeur de retour indiquant le statut de l'exécution du programme.
 */

int main(int argc, char *argv[]) 
{
    bool image_down;
    bool button_was_pressed = false;  // boolean used for debouncing
    uint32_t messages = DEFAULT;
    const int default_res_choice = 4;
    string format=".jpeg";
    in_port_t servPort = PortAddr; // First arg: local port

    // Create a socket for incoming connections
    int servSock = CreateSocket();

    // Construct the local address structure
    struct sockaddr_in servAddr = ConstructServAddr(servPort, true, NULL);

    BindAndListen(servSock, servAddr, 1);

    enum Mode {NORMAL, APPRENTISSAGE, RECONNAISSANCE};
    int mode(NORMAL);

    while(true) { 
        Odroid odroid;
        // Wait for a client to connect
        int clntSock = get_clntSock(servSock);

        do
        {
            Read_and_update_message(messages, odroid, clntSock, image_down, button_was_pressed);

            if(!(image_down))
            {
                Video video;
                video.setRes(default_res_choice);     // Setting camera with default resolution (352 x 288)

                while ((messages & ELE4205_OK) && !(image_down)) {
                    HandleClient(clntSock, messages, video,format);
                    Read_and_update_message(messages, odroid, clntSock, image_down, button_was_pressed);
                }

            } else {
                
                ssize_t recv_value = safeRecv(clntSock, &messages, sizeof(messages), 0);   //receive message (in case of ESC while no image)
            }

        } while(messages & ELE4205_OK);
        
        close(clntSock);
        cout << "Client session is over\n";
        return 0;
    }
}