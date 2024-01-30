

/**
 * \file handlers.cpp
 * \brief Fichier décrivant les fonctions utilisées par le client lors de l'utilisation de
 * l'application.
  
 * \brief Ce fichier contient les définitions des fonctions de traitement d'images et de demandes d'acquisition
 * ainsi que celles l'envoi de ces demandes serveur. Il définit également les fonctions gérant le clavier de l'utilisateur
 * et la réception des images provenant du serveur.
 **/

#include "handlers.h"

using namespace std;
using namespace cv;


/**    
 * \namespace patch
 * \brief  Namespace définissant une fonction manquante dans le namespace \b std . 
 * \brief  Le namespace \b patch crée un template définissant un fonction qui n'est pas incluse dans 
 * le namespace \b std. Cette fonction \b to_string redéfinie le type d'une variable \a n quelconque. 
 **/

namespace patch
{
 /**
  * \brief Conversion d'une variable \a n en une variable de type \b string .
  * \tparam T Type de la variable à convertir.
  * \param n Variable à convertir.
  * \return Retourne un \b string représentant la variable \e n .
 **/   

    template < typename T > string to_string( const T& n )
    {
        ostringstream stm ;
        stm << n ;
        return stm.str() ;
    }
}

/**
 * \Mat DecompressImage(vector<uchar> &compressedImageBuffer)
 * \brief Décompresse une image en utilisant le vecteur \a compressedImageBuffer comme tampon d'image compressée.
 * \param compressedImageBuffer Le tampon contenant les données de l'image compressée.
 * \return L'objet Mat décompressé représentant l'image.
 */

Mat DecompressImage(vector<uchar> &compressedImageBuffer)
{

    Mat decompressed_img;
    imdecode(compressedImageBuffer, IMREAD_COLOR, &decompressed_img);

    if (decompressed_img.empty()) 
        DieWithSystemMessage("decompression failed");
    
    return decompressed_img;
}

/**
 * \void KeyHandling(int &sock, uint32_t &messages) 
 * \brief Gère les entrées des touches de clavier à l'aide d'un socket
 * \param sock Identifiant du socket.
 * \param messages Les données du message.
 */

void KeyHandling(int &sock, uint32_t &messages)
{
    int key = waitKey(Delay);
    switch(key){
        case BUTTON1:
            messages &= RES01;  // Set the RES01 - RES01=MASK
            messages |= ISCHANGED;  // Set the ISCHANGED flag - ISCHANGED=MASK
            send(sock, &messages, sizeof(messages), 0);
            cout<<"RES01 chosen\n";
            break;
        case BUTTON2:
            messages &= RES02_1;  // Set the RES02
            messages |= RES02_2;
            messages |= ISCHANGED;  // Set the ISCHANGED flag
            send(sock, &messages, sizeof(messages), 0);
            cout<<"RES02 chosen\n";
            break;
        case BUTTON3:
            messages &= RES03_1;  // Set the RES03
            messages |= RES03_2;
            messages |= ISCHANGED;  // Set the ISCHANGED flag
            send(sock, &messages, sizeof(messages), 0);
            cout<<"RES03 chosen\n";
            break;
        case BUTTON4:
            messages |= RES04;  // Set the RES04
            messages |= ISCHANGED;  // Set the ISCHANGED flag
            send(sock, &messages, sizeof(messages), 0);
            cout<<"RES04 chosen\n";
            break;
        case BUTTON_P:
            messages ^= FORMAT_PNG; // change format
            messages |= ISCHANGED;  
            send(sock, &messages, sizeof(messages), 0);
            cout<<"format changed\n";
            break;
        case ESC:
            messages &= ELE4205_QUIT;  // Set the QUIT flag
            messages |= ISCHANGED;  // Set the ISCHANGED flag
            send(sock, &messages, sizeof(messages), 0);
            cout<<"ESC pressed\n";
            close(sock);
            exit(0);
    }
    messages |= ELE4205_OK;  // Set the OK flag
    messages &= DONE_CHANGING;
    send(sock, &messages, sizeof(messages), 0);
}

/**
 * \Mat receive_image(int &sock) 
 * \brief Reçoit une image provenant d'un socket et renvoi l'image reçue dans un objet \b Mat .
 * \param sock L'identifiant du socket.
 * \return L'objet Mat représentant l'image reçue.
 */

Mat receive_image(int &sock)
{
    int image_size;
    int recv_value = safeRecv(sock, &image_size, sizeof(image_size), 0);

    vector<uchar> compressedImageBuffer(image_size);

    size_t totalBytesRcvd = 0; // Count of total bytes received
    while (totalBytesRcvd < image_size) {
        ssize_t numBytes = safeRecv(sock, compressedImageBuffer.data() + totalBytesRcvd, image_size - totalBytesRcvd, 0);
        totalBytesRcvd += numBytes; 
    }
    // image received 
    Mat decompressed_img = DecompressImage(compressedImageBuffer);

    return decompressed_img;
}

/**
 * \void stream_image(int &sock,uint32_t &messages) 
 * \brief Gère l'affichage de l'image provenant du socket sur le serveur.
 * \param sock L'identifiant du socket.
 * \param messages Les données du message.
 */

void stream_image(int &sock,uint32_t &messages)
{

    Mat decompressed_img = receive_image(sock);
    imshow("ImageWindow", decompressed_img);
    KeyHandling(sock, messages);
}

/**
 * \void save_image(int &sock,int image_ID)  
 * \brief Enregistre une image à partir du socket du serveur avec un identifiant.
 * \param sock L'identifiant du socket.
 * \param image_ID L'identifiant de l'image.
 */

void save_image(int &sock, int image_ID)
{
    Mat decompressed_img = receive_image(sock);
    string name = "capture" + patch::to_string(image_ID) + ".png";
    imwrite(name, decompressed_img);            
}

/**
 * \void handle_odroid_message(int &sock, uint32_t &messages, bool &image_down, bool &push_button) 
 * \brief Gère le message de l'Odroid qui indique l'état du bouton et des données de l'image.
 * \param sock L'identifiant du socket.
 * \param messages Les données du message.
 * \param image_down Indique si l'image est reçue.
 * \param push_button Indique si le bouton est enfoncé.
 */

void handle_odroid_message(int &sock, uint32_t &messages, bool &image_down, bool &push_button)
{
    int recv_value = safeRecv(sock, &messages, sizeof(messages), 0);
    if((messages & LIGHTMSK )!= 0)
    {
        image_down = true;
    } else {
        image_down = false;
    } 
    if((messages & BUTTON_MSK )!= 0)
    {
        push_button = true;
    } else {
        push_button = false;
    } 
}

/**
 * \void show_and_save_image(int &image_ID, bool push_button,int &sock, uint32_t &messages, const string &data_base_path)  
 * \brief Affiche et enregistre une image traitée avec une méthode de détection des visages.
 * \param image_ID L'identifiant de l'image.
 * \param push_button Indique si le bouton est enfoncé.
 * \param sock L'identifiant du socket.
 * \param messages Les données du message.
 * \param data_base_path Le sous-répertoire où l'image est enregistrée.
 */

void show_and_save_image(int &image_ID, bool push_button,int &sock, uint32_t &messages, const string &data_base_path)
{
    image_ID++;
    push_button = false;

    Mat decompressed_img = receive_image(sock);
    pid_t child_pid;
    child_pid = fork();
    if (child_pid==0)
    {      
        // Perform face detection, draw rectangles, and save the image
        detect_and_save_faces(decompressed_img, image_ID, data_base_path);
        exit(0);
    } else {
        imshow("ImageWindow", decompressed_img);
        KeyHandling(sock, messages);
    } 

}

/**
 * \void detect_and_save_faces(Mat& image, int &image_ID, const string &data_base_path)  
 * \brief Détecte et enregistre les visages sur l'image reçue.
 * \param image L'image à traiter.
 * \param image_ID L'identifiant de l'image.
 * \param data_base_path Le sous-répertoire où les visages détectés sont enregistrés.
 */
void detect_and_save_faces(Mat& image, int &image_ID,const string &data_base_path)
{
    string path_to_csv = "./faces.csv";
    CascadeClassifier face_cascade;
    if (!face_cascade.load("haarcascade_frontalface_default.xml")) {
        cerr << "Error loading face cascade." << endl;
        return;
    }

    vector<Rect> faces;
    Mat gray_image;
    Mat cropped_faces;

    // Convert the image to grayscale for face detection
    cvtColor(image, gray_image, COLOR_BGR2GRAY);
    equalizeHist(gray_image, gray_image);

    // Detect faces
    face_cascade.detectMultiScale(gray_image, faces, 1.1, 3, 0, Size(30, 30));
 
    // Draw rectangles around detected faces
    for (int i = 0; i < faces.size(); ++i) {
        cropped_faces = image(faces[i]);
        // Save the image with rectangles drawn around faces
        string name = data_base_path + "/" + "capture" + patch::to_string(image_ID) + ".png";
        imwrite(name, cropped_faces);
        ++image_ID;
    }
}