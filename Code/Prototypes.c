
#include "Prototypes.h"

#define LARGEUR_CONSOLE 100
#define LONGUEUR_LIGNE 255

struct PBM
{
	int nbrColonnes;
	int nbrLignes;
};

typedef struct PBM PBM;

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



FILE *ouvertureImage(char* chemin, char* mode)
{

			FILE* fichier = fopen(chemin, "a");

			if(fichier != NULL)
			{
				return fichier;
			}
}



int	getKey(void)
{
	pid_t pid_child;
	pid_t pid_parent;
	char keyPressed;

	pid_parent = getpid();
	pid_child = fork();

	switch(pid_child)
	{
		case -1:
			printf("erreur du fork");
			exit (1);
			break;
		case 0:
			while (keyPressed != 'q')
				keyPressed = getchar();
			kill(pid_parent, 9);
			exit (0);
			break;
		default:
			break;
	}
}



void printfCentered (int longeurChaine, char *chaine, int *largeurConsole)
{
	unsigned int n;
	for (n = 0; n < (*largeurConsole-longeurChaine) / 2; n++)
	{
		printf(" ");
	}
	printf("%s\n", chaine);
}


/*
void conversion_image()
{
	int j;
	int* nb_colonne = NULL;
	int* nb_ligne = NULL;
	int* Tableau = NULL;
	FILE* pbm_j = fopen("pbm_j", "r");

	fseek(pbm_j, 4, SEEK_SET);
	nb_colonne = fgetc(pbm_j);
	fseek(pbm_j, 6, SEEK_SET);
	nb_ligne = fgets(Tableau, 2, pbm_j);

	char** Tableau = malloc(nb_ligne * sizeof(int*));
	for(int i = 0; i < nb_colonne; i++)
	{
		Tableau[i] = malloc(nb_colonne * sizeof(int));

		if(Tableau == NULL)
		{
			exit(0);
		}

		for(i = 0; i <= nb_ligne; i++)
		{
			for(j = 0; j <= nb_colonne; j++)
			{
				fscanf("%d", &Tableau);

			}
		}

	}

	fclose("pbm_j");
}

*/



void lectureDimensionsPBM(FILE* fichier, int* lignes, int* colonnes)
{
	char ligneLue[LONGUEUR_LIGNE];

	do
	{
		fgets(ligneLue, LONGUEUR_LIGNE, fichier);
	}
	while(ligneLue[0] != '#');

	sscanf(ligneLue, "#%d %d", lignes, colonnes);
}

void conversionPBM(FILE* fichier, int* lignes, int* colonnes,int ***tableauPBM)
{
	char ligneLue[LONGUEUR_LIGNE];

	int ligneEcrite, colonneEcrite;

	lectureDimensionsPBM(fichier, lignes, colonnes);

	if (lignes == 0 || colonnes == 0)
	{
		printf("Erreur de réception des dimensions de l'image");
	}

	fgets(ligneLue, LONGUEUR_LIGNE, fichier);
	printf("%s\n", ligneLue);
	
}

int** tableauBidim(int lignes, int colonnes)
{
	int **tableau = malloc(lignes * sizeof(int));
//	int *tableauBis = malloc(colonnes * lignes * sizeof(int));
	int i;

	for(i = 0; i < lignes; i++)
	{
		tableau[i] = malloc(colonnes * sizeof(int));
	}

return tableau;
}

void freeTableau(int **tableau, int lignes)
{
	free(tableau[0]);
	free(tableau);
}



void	getTerminalSize(int * width, int * height)
{
	struct winsize size_terminal;
	ioctl(0, TIOCGWINSZ, &size_terminal);

	*width = size_terminal.ws_col;
	*height = size_terminal.ws_row;
}


