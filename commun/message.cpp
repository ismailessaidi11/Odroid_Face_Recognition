/**
 * \file 
 * \brief Définition des messages d'arrêt de la communication client-serveur
 
 * \brief Ce fichier contient les fonctions d'affichage d'un message d'erreur destiné à l'utilisateur. 
 * Cette erreur survient lorsque la connection n'arrive pas à être établie entre le serveur et le client.
 *  Les fonctions quittent également le programme après que l'affichage de l'erreur ait été terminé. 
 **/

#include "message.h" 

using namespace std;

/**
 * \void DieWithUserMessage(const std::string &message, const std::string &detail)  
 * \brief La fonction affiche un message d'erreur détaillé destiné à l'utilisateur lors de son utilisation. 
 * L'affichage se fait via la sortie d'erreur standard (cerr). La fonction quitte ensuite le programme.
 * 
 * \param message Le message d'erreur principal à afficher.
 * \param detail Les détails supplémentaires pour détailler l'erreur.
 */

void DieWithUserMessage(const std::string &message, const std::string &detail) {
    std::cerr << message << ": " << detail << std::endl;
    exit(1);
}

/**
 * \void DieWithSystemMessage(const std::string &message)  
 * \brief La fonction affiche un message d'erreur système sur la sortie standard (cout) et quitte ensuite le
 * programme.
 * 
 * \param message Le message d'erreur système à afficher.
 */

void DieWithSystemMessage(const std::string &message) {
    cout<< message.c_str();
    exit(1);
}
