/**
 * \file 
 * \brief Déclaration des fonctions de messages d'arrêts de la communication client-serveur

 * \brief Ce fichier contient les bibliothèques  utilisées et les déclarations des fonctions envoyant 
 * les messages indiquant que la communication n'est pas active entre le serveur et le client. 
 **/


#ifndef MESSAGE_H
#define MESSAGE_H

#include <string>
#include <iostream>
#include <cstdlib>
#include <cstring>

void DieWithUserMessage(const std::string &message, const std::string &detail);
void DieWithSystemMessage(const std::string &message);

#endif
