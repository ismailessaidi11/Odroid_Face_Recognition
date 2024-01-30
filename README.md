## Usage
La caméra se lance avec la résolution par défaut (352x288) et avec le format jpeg.
Afin de changer la résolution il faut appuyer sur les boutons:

* 1 : résolution (320x176)
* 2 : résolution (320x240)
* 3 : résolution (352x288)
* 4 : résolution (432x240)

Pour changer le format de l'image il faut appuyer sur le **bouton P** qui agit comme un "toggle" donc le format change à chaque fois qu'on appuie (en commençant par format jpeg).

En appuyant sur le bouton de l'Odroid on peut prendre une capture d'image qui enregistre les images coupées à la taille des visages détectés dans le disque.
S'il n'y a pas assez de lumière, la caméra affiche une image noire.

## A inclure
librairie a inclure:

find_package(OpenCV REQUIRED)
target_link_libraries(Server  ${OpenCV_LIBS})

fichier a telecharger:

haarcascade_frontalface_default.xml
## Séquence de compilation
Sur le terminal du serveur:

```
bash
sudo /users/Cours/ele4205/commun/scripts/ifconfig-enp0s-up
source /usr/local/opt/poky/2.1.3/environment-setup-aarch64-poky-linux
cd build
cmake ..
make
code --extensions-dir /export/tmp/${USER}/vscode-ext .
```

Sur le terminal du client:
```
cd build
cmake ..
make
code --extensions-dir /export/tmp/${USER}/vscode-ext .
```
## Lancement
Il suffit de lancer un run without debug (f5) dans le vscode du serveur d'abord puis lancer un autre run without debug (f5) dans le client.

## Copyrights
L'algorithme de capture de vidéo est inspiré du travail de derek molloy:
https://github.com/derekmolloy/boneCV/