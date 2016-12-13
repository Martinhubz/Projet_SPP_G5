#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include "Proto_lanceur.h"
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>

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
void ecritureHisto(char *typeEcran, char *parametre)
{
	pid_t parent = getpid();
	pid_t pid = fork();	/*Création du processus fils*/
	
	if(pid == 1)
	{
		printf("Erreur de la création du processus fils");
	}

	else if(pid > 0)
	{
		int status;

		/*Le processus attend la fin du processus fils*/
		waitpid(pid, &status, 0);
	}

	else
	{
		time_t temps;
		time(&temps);
/*Détermination de l'heure locale*/
		struct tm* tempsLocal = localtime(&temps);
		char chaineTemps[25], ligneActuelle[25];

		strcpy(chaineTemps, asctime(tempsLocal));

		chaineTemps[19] = '\0';

		FILE* fichier = fopen("/home/martin/ExiaSaver/Historique", "a");

		if(fichier != NULL)
		{
		/*Ecriture des infos écran dans le fichier Historique*/
			fprintf(fichier, "%s | %s | %s\n", chaineTemps, typeEcran, parametre);
		}

		else
		{
			printf("Erreur lors de l'ouverture du fichier");
		}

		fclose(fichier);

	}
}

void lectureHisto()
{
	int choix = 0, i = 0;
	char caractereActuel;

	FILE* fichier = fopen("/home/martin/ExiaSaver/Historique", "r");

	while(choix != 3)
	{
	system("clear");

	/*Menu Historique*/
		printf("\n\nMenu:\n1- Historique\n2- Statistiques\n3- Exit\n\n");
		scanf("%d", &choix);

		switch(choix)
		{
			case 1:
			{
				char ligneHistorique[100] = {0};

				rewind(fichier);

				for(i = 0; i < 2; i++)
				{
				/*On passe les deux premières lignes*/
					fgets(ligneHistorique, sizeof ligneHistorique, fichier) != NULL;
				}

				system("clear");

			/*On affiche la ligne lue du fichier jusqu'à la dernière*/
				while(fgets(ligneHistorique, sizeof ligneHistorique, fichier) != NULL) 
				{
					printf("%s", ligneHistorique);
				}



			break;
			}

			case 2:
			{
				system("clear");
				printf("Machine a statistiques defaillante, veuillez reessayer plus tard\n\n");

			break;
			}

			case 3:
			{
				system("exit");

			break;
			}
		
			default:
			{
				printf("Erreur, réesayez");
			}
		}
	}
	fclose(fichier);
}
	
