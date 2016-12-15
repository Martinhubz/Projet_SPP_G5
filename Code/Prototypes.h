#include <unistd.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <stdio.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <string.h>
#include <time.h>

/*Ecrit les differentes infos dans le fichier historique*/
void ecritureHisto(char *typeEcran, char *parametre);

/*Lit les infos du fichier historique*/
void lectureHisto();

/*Ouvrir l'image*/
FILE *ouvertureImage(char* chemin, char* mode);

/*recupere la saisie*/
int getKey(void);

/*lit les dimension de l'image*/
void lectureDimensionsPBM(FILE* fichier, int* lignes, int* colonnes);

/*conversion d'une image PBM en tableau*/
void conversionPBM(FILE* fichier, int* lignes, int* colonnes, int*** tableauPBM);

/*création d'un tableau à deux dimensions*/
int** tableauBidim(int lignes, int colonnes);

/*librération de la mémoire allouée au tableau à 2 dimensions*/
void freeTableau(int **tableau, int lignes);

void getTerminalSize(int *width, int* height);

/*affichage centrée de la chaine*/
void printfCentered(int longueurChaine, char *chaineEcrite, int *largeurConsole);
