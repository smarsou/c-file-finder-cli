#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <errno.h>
#include "lsRec.h"

void tabulation(int tab){
	for (int i=0; i<tab; i++){
		printf("	");
	}
	printf("|");
}

void lsrec(char *dir, int tab){
    struct dirent *d;
    struct dirent **namelist; // namelist[i]->d_type est un entier qui permet de savoir si le pointeur nameliste[i] correspond à un répertoire ou un fichier (4 == repertoire, 8 == fichier)
	// test erreur de lecture du repertoire courant
	DIR *dh = opendir(dir);
	if (!dh)
	{
		if (errno == ENOMEM){
			perror("Memory error");
			printf("%s %d\n ", dir, errno);
		}
		if (errno == ENOENT)
		{
			//If the directory is not found
			perror("Directory doesn't exist or was just removed by another process");
			printf("%s %d\n ", dir, errno);
		}
		else
		{
			//If the directory is not readable then throw error and exit
			perror("Unable to read directory");
		}
		exit(EXIT_FAILURE); //ligne de code à passer en commentaire pour ignorer les répertoires innaccessibles 
	}

	int n = scandir(dir, &namelist, 0, alphasort);
	if (n==-1){  // Si y'a une erreur quelconque on skip cette apel récursif
		printf("\nERROR skip this folder\n");
		return;
		}
    for (int i =0; i< n; i++){
        char letter[]= {namelist[i]->d_name[0], '\0'};
        
        if (!strcmp(letter,".")){
            continue; // Si on tombe sur un dossier ou fichier caché, on ne l'affiche pas.
        }

		tabulation(tab); //Permet d'indenter l'affichage
		char * name = namelist[i]->d_name;
		if (namelist[i]->d_type!=4){
			printf("%s/%s \n", dir,name);
			continue;
		}
		//On met un peu de couleur quand on affiche un dossier
		printf("\033[0;34m");
		printf("%s/%s \n", dir,name);
		printf("\033[0;37m");
		
		char str1[255];
		strcpy(str1, dir);
		strcat(str1, "/");
		strcat(str1,name);
		tab++;
		lsrec(str1,tab);
		tab--;
	}
    free(namelist);    
}
