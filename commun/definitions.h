

/**
 * \brief Délai pour la fonction waitKey.
 */
#define Delay  30

/**
 * \brief Code pour la touche ESC
 */
#define ESC 1048603

/**
 * \brief Code pour la touche 1
 */
#define BUTTON1 1048625

/**
 * \brief Code pour la touche 2
 */
#define BUTTON2 1048626

/**
 * \brief Code pour la touche 3
 */
#define BUTTON3 1048627

/**
 * \brief Code pour la touche 4
 */
#define BUTTON4 1048628

/**
 * \brief Code pour la touche P
 */
#define BUTTON_P 1048688


/**
 * \brief Code pour indiquer qu'un bouton du clavier a été pressé
 */
#define ELE4205_OK  0x00000001

/**
 * \brief Code pour indiquer qu'aucun bouton du clavier n'a été pressé
 */
#define ELE4205_QUIT  0xFFFFFFFE

/**
 * \brief Code pour la résolution 1
 */
#define RES01  0xFFFFFFF9

/**
 * \brief Code pour le premier bit de la résolution 2
 */
#define RES02_1  0xFFFFFFFB

/**
 * \brief Code pour le second bit de la résolution 2
 */
#define RES02_2  0x00000002

/**
 * \brief Code pour le premier bit de la résolution 3
 */
#define RES03_1  0xFFFFFFFD

/**
 * \brief Code pour le second bit de la résolution 3
 */
#define RES03_2  0x00000004

/**
 * \brief Code pour la résolution 4
 */
#define RES04  0x00000006

/**
 * \brief Code pour le format JPEG
 */
#define FORMAT_JPEG  0xFFFFFFF7

/**
 * \brief Code pour le format PNG
 */
#define FORMAT_PNG  0x00000008

/**
 * \brief Code pour valeur par défaut
 */
#define DEFAULT  0x00000005

/**
 * \brief Changement de résolution et format
 */
#define ISCHANGED  0x00000010

/**
 * \brief Résolution et format ont terminé de changer
 */
#define DONE_CHANGING  0xFFFFFFEF

/**
 * \brief Masque pour le choix de résolution
 */
#define RESMSK  0x00000006

/**
 * \brief Masque pour le choix de format
 */
#define FORMATMSK  0x00000008

/**
 * \brief Lumière absente
 */
#define NO_LIGHT 0x00000020

/**
 * \brief Lumière présente
 */
#define LIGHT 0xFFFFFFDF

/**
 * \brief Bouton appuyé
 */
#define BUTTON_PRESSED 0x00000040

/**
 * \brief Bouton n'est pas appuyé
 */
#define BUTTON_NOT_PRESSED 0xFFFFFFBF

/**
 * \brief Masque pour la lumière
 */
#define LIGHTMSK 0x00000020

/**
 * \brief Masque pour le bouton
 */
#define BUTTON_MSK 0x00000040

/**
 * \brief Définition du port sur lequel un socket TCP est ouvert
 */
#define PortAddr  4099

/**
 * \brief Définition de l'adresse IP du serveur
 */
#define SERVER_IP  "192.168.7.2"
