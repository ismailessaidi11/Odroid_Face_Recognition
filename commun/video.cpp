/**
 * \file 
 * \brief Fonctions de contrôle de la caméra par le serveur.

 * \brief Ce fichier contient les commandes d'ouverture et de fermeture de la caméra ainsi que les résolutions existantes.
 * Ces fonctions sont utilisées par le serveur en fonction des demandes du client ou d'erreur de fonctionnement.
 * 
 **/

#include "video.h"
using namespace std;
using namespace cv;



namespace
{
    const int num_res = 13;
    Resolution resolutions[num_res] = {
        { 176, 144, 0.0},
        { 160, 120, 0.0},
        { 320, 176, 0.0},
        { 320, 240, 0.0},
        { 352, 288, 0.0}, 
        { 432, 240, 0.0}, 
        { 800, 600, 0.0}, 
        { 864, 480, 0.0},
        { 960, 544, 0.0}, 
        { 960, 720, 0.0}, 
        {1184, 656, 0.0}, 
        {1280, 720, 0.0},
        {1280, 960, 0.0}};

} 

Video::Video(int Port_ID_cam , int video_duration , string ID_USB_cam)
        : Port_ID_cam(Port_ID_cam), video_duration(video_duration), ID_USB_cam(ID_USB_cam)
{
    //open camera
    capture = VideoCapture(0);
    if (!capture.isOpened()) {
        capture.open(ID_USB_cam);  
        if (!capture.isOpened()) {
            cout << "Failed to connect to the camera." << endl;
            exit(0);
        }
    }
} 

    /** \Video::~Video
     * \brief Destructeur de la classe Video.
     */
Video::~Video() {
    //close camera
    capture.release();
}

    /** \VideoCapture Video::getCapture
     * \brief Obtient l'objet de capture vidéo.
     * \return L'objet de capture vidéo.
     */

VideoCapture Video::getCapture()
{
    return capture;
}

    /**
     * \void Video::setRes
     * \brief Définit la résolution de la vidéo.
     * \param choice Indice de la résolution dans le tableau resolutions.
     */
void Video::setRes(int choice)
{

    res = resolutions[choice];

    capture.set(CV_CAP_PROP_FRAME_WIDTH,res.x);
    capture.set(CV_CAP_PROP_FRAME_HEIGHT,res.y);
    cout<<"resolution set to: ("<<res.x<<"x"<<res.y<<")\n";
}

    /** \void Video::saveVideo
     * \brief Enregistre une vidéo capturée à partir de la caméra.
     */
void Video::saveVideo()
{
    VideoWriter video("capture-liv1.avi", CV_FOURCC('M', 'J', 'P', 'G'), res.fps, Size(res.x, res.y));

    for (int i = 0; i < video_duration * res.fps; ++i) {
        Mat frame;
        capture >> frame;
        if (frame.empty()) {
            cout << "Failed to capture an image" << endl;
            exit(0);
        }

        video.write(frame);
    }
}

/**
 * \brief Initialise les FPS pour chaque résolution.
 * \param video Objet de capture vidéo.
 */

void initFps(Video video)
{
    VideoCapture capture = video.getCapture();
    cout << "Available resolutions:" << endl;
    for (int i=0; i < num_res; ++i){

        capture.set(CV_CAP_PROP_FRAME_WIDTH,resolutions[i].x);
        capture.set(CV_CAP_PROP_FRAME_HEIGHT,resolutions[i].y);
        Mat frame;

        struct timespec start, end;

        int frames=10;
        for(int j=0; j<frames + 2; j++){
            if (j == 2){
                clock_gettime(CLOCK_REALTIME, &start);
            }
            capture >> frame;
            if(frame.empty()){
                cout << "Failed to capture an image" << endl;
                exit(0);
            }
        }

        clock_gettime(CLOCK_REALTIME, &end);
        double difference = (end.tv_sec - start.tv_sec) + (double)(end.tv_nsec - start.tv_nsec)/1000000000.0;

        resolutions[i].fps = frames/difference;
        cout << "     " << i << ": " << resolutions[i].x << " X " << resolutions[i].y << " FPS " << resolutions[i].fps << endl;
    }

}