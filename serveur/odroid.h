/**
 * \file 
 * \brief Fichier déclarant une fonction et définissant une classe pour contrôler le bouton et la photodiode reliés à l'Odroid-C2

 * \brief Ce fichier définit la classe \b Odroid qui permet au serveur de recevoir toutes les informations provenant 
 * de la photodiode et du bouton pour déterminer si la prise de photo doit être effectuée. Les fonctions utilisées pour enregistrer ces 
 * informations sont décrites dans ce fichier.
 **/


#ifndef ODROID_H_INCLUDED
#define ODROID_H_INCLUDED

#include <fstream>
#include <string>
#include <iostream>


using namespace std;

/**
 * \class Odroid 
 * \brief Description de la classe gérant les interactions entre la photodiode, le bouton et l'Odroid-C2

 * \brief Cette classe permet de contrôler des composantes branchées à l'Odroid-C2, dans ce cas-ci une photodiode et un bouton. Les informations
 * incluses dans la classe permettent de détecter la lumière et contrôler et déterminer l'état d'un bouton. 
 **/

class Odroid
{
    private:
   
    int adc_value; /**< Valeur ADC lue à partir du chemin spécifié. */
    string adc_path; /**< Chemin du fichier de la valeur ADC. */
    int button_value; /**< État actuel du bouton (0 ou 1). */
    string button_path; /**< Chemin du fichier d'état du bouton. */
    string gpioPath; /**< Chemin du fichier GPIO. */
    int gpio_nb; /**< Numéro GPIO associé au bouton. */
    string directionPath; /**< Chemin du fichier de direction GPIO. */
    string direction; /**< Direction du GPIO (entrée ou sortie). */
    
    public:

    /**
     * \brief Constructeur de la classe Odroid.
     * \param adc_path Chemin du fichier de la valeur ADC.
     * \param button_path Chemin du fichier d'état du bouton.
     * \param gpioPath Chemin du fichier GPIO.
     * \param directionPath Chemin du fichier de direction GPIO.
     * \param gpio_nb Numéro GPIO associé au bouton.
     * \param direction Direction du GPIO (entrée ou sortie).
     **/

        Odroid(string adc_path = "/sys/class/saradc/ch0",
                string button_path = "/sys/class/gpio/gpio228/value",
                string gpioPath = "/sys/class/gpio/export",
                string directionPath = "/sys/class/gpio/gpio228/direction",
                int gpio_nb = 228, string direction = "in");
    
        void set_button();
        bool no_light();
        bool button_pressed();
};

int read_file(string path);
void write_file(string path, int int_value, string string_value, bool num_value);
#endif
