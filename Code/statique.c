#include "Prototypes.h"

void image ()
{
        int i = 0, j = 0;

        for (i = 0 ; i < 10 ; i++)
        {
		printf_center(6);
                for (j = 0 ; j < 6 ; j++)
                {
			if(affichage[i][j] == 0)
			{
                        	printf(" ");
			}
			else
			{
				printf("X");
			}
                }
                printf("\n");
        }
        return 0;
}

int main()
{
	image();
	return 0;
}*/


void conversion_image()
{
	int j;
	int nb_colonne = NULL;
	int nb_ligne = NULL;
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
