#include "Prototypes.h"

#define NOMBRE_IMAGES 10	/*Nombre d'images PBM pour le niveau statique*/
#define LIGNES_MAX 100		/*Position initiale Y maximale de l'avion*/
#define COLONNES_MAX 100	/*Position initiale X maximale de l'avion*/

int main(int argc, char** argv)
{
	int i;
/*	char ecranChoisi[3][5] = {{'s','t','a','t'},{'d','y','n','a'},{'i','n','t','e'}};*/
	char ecranChoisi[3][5]={"stat","dyna","inte"};
	system("clear");


	if(argc >= 2)	/*On vérifie si le programme a été exécuté avec un paramètre*/
	{
		if(strcmp(argv[1], "-stat") == 0) 	/*On compare le paramètre à "-stat"*/
		{
			lectureHisto();			/*Ouverture du menu statistiques/historique*/
		}

		else
		{
			printf("Syntaxe incorrecte\n");
		}
 	}
 	else 
 	{
		char ligne[20], colonne[20], n;
		char *parametre = NULL;
		char numeroImage[20];
		int m, ligneRand, colonneRand, compteurStat, compteurDyna, compteurInte;

		srand(time(NULL));
		n = rand()%3;

		switch(n)	/*Détermination léatoire du paramètre à utiliser*/
		{
			case 0:
			{
			compteurStat++;
			m = rand()%NOMBRE_IMAGES;
			sprintf(numeroImage, "%d", m);	/*Conversion de m en char*/

			parametre = strcat(numeroImage, ".PBM");	/*ex: 4.PBM*/

			break;
			}

			case 1:
			{
			compteurDyna++;
			parametre = NULL;

			break;
			}

			case 2:
			{
			compteurInte++;

		/* Détermination aléatoire de la position intitale de l'avion*/
			ligneRand = rand()%LIGNES_MAX;
			colonneRand = rand()%COLONNES_MAX;

			sprintf(ligne, "%d", ligneRand);
			sprintf(colonne, "%d", colonneRand);

			parametre = strcat(strcat(ligne, "x"), colonne);

			break;
			}

			default:
				printf("Erreur");
			break;
		}

		ecritureHisto(ecranChoisi[n], parametre);
	/*Exécution de l'exécutable choisi avec son paramètre*/
		execl(strcat(getenv("EXIASAVER_HOME"), ecranChoisi[n]), ecranChoisi[n], parametre, NULL);

	}
	
	return 0;
}

/*Fonction qui écrit les infos de l'écran lancé dans le fichier Historique*/



