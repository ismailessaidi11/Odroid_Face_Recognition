/**
 * \file 
 * \brief Fichier décrivant les fonctions de contrôle de la photodiode et du bouton branchés à l'Odroid-C2

 * \brief Ce fichier contient les fonctions qui permettent de recevoir et traiter les informations fournies par la photodiode
 * et le bouton reliés à l'Odroid-C2. Ceux-ci sont utilisés par l'utilisateur pour prendre les photos. Lorsque le bouton est pesé, le serveur 
 * fait une capture de l'image sur la caméra. La photodiode indique au serveur si la luminosité est adéquate pour prendre la photo.
 **/

#include "odroid.h"

using namespace std;


Odroid::Odroid(string adc_path, string button_path, string gpioPath, string directionPath,
                int gpio_nb, string direction)
        :adc_path(adc_path), button_path(button_path), gpioPath(gpioPath),gpio_nb(gpio_nb),
        directionPath(directionPath), direction(direction)
{
        set_button();
}

    /**
     * \fn no_light
     * \brief Vérifie s'il n'y a pas de lumière.
     * \return Vrai s'il n'y a pas de lumière, faux sinon.
    **/
bool Odroid::no_light()
{
        adc_value = read_file(adc_path);
        return (adc_value>1000); // (1023) corresponds to no_light and around 900 is when exposed to light
}

/**
 * \fn Odroid::button_pressed
 * \brief Vérifie si le bouton est pressé (état du bouton est 0).
 * \return Vrai si le bouton est pressé, faux sinon.
 **/
bool Odroid::button_pressed()
{
        button_value = read_file(button_path);
        return (button_value == 0);
}

    /**
     * \fn Odroid::set_button
     * \brief Défini l'état du bouton.
     **/
void Odroid::set_button()
{
        write_file(gpioPath, gpio_nb, "", true);
        write_file(directionPath, 0, direction, false);
}

/**
 * \int read_file
 * \brief Lit une valeur entière provenant des fichiers spécifiés.
 * \param path Chemin du fichier.
 * \return La valeur entière qui est lue par la fonction est retournée.
 **/
int read_file(string path)
{
        int value;
        ifstream file;
        file.open(path.c_str());
        if (file.is_open()) {
                file >> value;
                file.close();
        } else {
                cout << "Unable to open the file for reading.\n";
                value = 404;
        }
        return value;
}

/**
 * \void write_file
 * \brief Écrit une valeur entière ou une chaîne de caractères dans le fichier spécifié.
 * \param path Chemin du fichier.
 * \param int_value Valeur entière à écrire (utilisée si \a num_value est vrai).
 * \param string_value Valeur du \a string à écrire (utilisée si \a num_value est faux).
 * \param num_value Flag indiquant s'il faut écrire une valeur entière ou une chaîne de caractères.
 */
void write_file(string path, int int_value, string string_value, bool num_value)
{
        
        ofstream file;
        file.open(path.c_str());
        if (file.is_open())
        {
                if (num_value)
                {
                        file << (int_value);
                } else {
                        file << (string_value);
                } 
                file.close();
        } else {
                cout << "Unable to open the file for writing.\n";
        } 
}

