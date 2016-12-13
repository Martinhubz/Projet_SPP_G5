#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include "Proto_lanceur.h"
#include <string.h>
#include <sys/wait.h>
#include <sys/types.h>

#define NOMBRE_IMAGES 10
#define LIGNES_MAX 100
#define COLONNES_MAX 100

int main(int argc, char** argv)
{
	int i;
//	char ecranChoisi[3][5] = {{'s','t','a','t'},{'d','y','n','a'},{'i','n','t','e'}};
	char ecranChoisi[3][5]={"stat","dyna","inte"};
	system("clear");


	if(argc >= 2)	//On vérifie si le programme a été exécuté avec un paramètre
	{
		if(strcmp(argv[1], "-stat") == 0) //On compare le paramètre à "-stat"
		{
			lectureHisto();//Ouverture du menu statistiques/historique
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

		switch(n)	//Détermination du paramètre à utiliser
		{
			case 0:
			{
			compteurStat++;
			m = rand()%NOMBRE_IMAGES;
			sprintf(numeroImage, "%d", m);	//Conversion de m en char

			parametre = strcat(numeroImage, ".PBM");	//ex: 4.PBM

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
//		execl(strcat(getenv("EXIASAVER_HOME"), ecranChoisi[n]), ecranChoisi[n], parametre, NULL);

	}
	
	return 0;
}

void ecritureHisto(char *typeEcran, char *parametre)
{
	pid_t parent = getpid();
	pid_t pid = fork();	//Création du processus fils
	
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
		struct tm* tempsLocal = localtime(&temps);
		char chaineTemps[25], ligneActuelle[25];
		strcpy(chaineTemps, asctime(tempsLocal));

		chaineTemps[19] = '\0';

		FILE* fichier = fopen("/home/martin/ExiaSaver/Historique", "a");

		if(fichier != NULL)
		{
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

	while(choix != 1 && choix != 2)
	{
		printf("\n\nMenu:\n1-Historique\n2-Statistiques\n\n");
		scanf("%d", &choix);

		switch(choix)
		{
			case 1:
			{
				char ligneHistorique[100] = {0};

				rewind(fichier);

				for(i = 0; i < 2; i++)
				{
					fgets(ligneHistorique, sizeof ligneHistorique, fichier) != NULL;
				}

				system("clear");

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
		
			default:
			{
				printf("Erreur, réesayez");
			}
		}
	}
	fclose(fichier);
}
	
