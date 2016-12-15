#include "Prototypes.h"


int main(int argc, char *argv[])
{
	
	char messageRefresh[] = "L'heure s'actualisera dans 10sec";
	char chaineMessage[100];
	char repImage[] = "/home/martin/ExiaSaver/PBM/Horloge_";
	char cheminImage[100];
	char chaineTemps[100];
	char chaineLigne[100];
	char image0[6][4] = {{1,1,1}, {1,0,1}, {1,0,1}, {1,0,1}, {1,1,1}};

	int tempsRefresh = 10; 
	int i, j, h10, h01, m10, m01, s10, s01;
	int largeurConsole, hauteurConsole;

	getTerminalSize(&largeurConsole, &hauteurConsole);

	time_t temps;
	struct tm* tempsLocal;

	strcpy(chaineMessage, messageRefresh);
	strcpy(cheminImage, repImage);

	FILE* image[10];
	FILE* fichier;

	for(i = 0; i < 10; i++)
	{

		sprintf(cheminImage, "/home/martin/ExiaSaver/PBM/Horloge_%d", i);
		strcat(cheminImage, ".pbm");

		image[i] = ouvertureImage(cheminImage, "r+");
	}

//	tableau = conversionImage();
	getKey();

	while(1)
	{
		time(&temps);
		tempsLocal = localtime(&temps);

		h10 = tempsLocal->tm_hour / 10;
		h01 = tempsLocal->tm_hour % 10;
		m10 = tempsLocal->tm_min / 10;
		m01 = tempsLocal->tm_min % 10;
		s10 = tempsLocal->tm_sec / 10;
		s01 = tempsLocal->tm_sec % 10;

		

		chaineMessage[32] = '\0';

		for(i = 0; i < tempsRefresh; i++)
		{
			system("clear");

			for(j = 0; j < (hauteurConsole-5)/2; j++)
			{
				printf("\n");
			}
/*
			for(j = 0; i < 5; j++)
			{
				sprintf(chaineLigne, "%s%s %s %s%s %s %s%s", nombre[h10][j], nombre[h01][j], nombre[10][j], nombre[m10][j], nombre[m01][j], nombre[10][j], nombre[s10][j], nombre[s01][j]);				printfCentered(strlen(chaineLigne), chaineLigne, largeurConsole);
			}

			for(j = 0; j < ((hauteurConsole-5)/2) - 1; j++)
			{
				printf("\n");
			}
*/		
			chaineMessage[32 + i] = '.';
			chaineMessage[33 + i] = '\0';

			printfCentered(strlen(chaineMessage), chaineMessage, &largeurConsole);
			sleep(1);

		}

	}


	for(i = 0; i < 10; i++)
	{
		fclose(image[i]);
	}

	return 0;
}
