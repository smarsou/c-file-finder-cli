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

//Fonction de filtre du fichier name en fonction de l'option et des paramètres d'option
int filter(char * name, char *option, char * paramsOption[]){
	if (!strcmp(option,"NULL")){ // Si il n'y a pas d'option, on affiche alors tous les fichiers (return 1)
		return 1;
	}
	if (!strcmp(option,"-name")){ //Si on filtre par nom (-name)
		if (!strcmp(name, paramsOption[0])){ //Si le nom est le même que celui passé en paramètre d'option
			return 1;
		}else{
			return 0;
		}
	}
	else{
		printf("Option non prise en compte");
		return 0;
	}
}

void lsrec(char *dir, int tab, char *option, char * paramsOption[]){
    struct dirent *d;
    struct dirent **namelist; // namelist[i] est un pointeur, namelist[i]->d_type est un entier, il permet de savoir si le pointeur nameliste[i] correspond à un répertoire ou un fichier (4 == repertoire, 8 == fichier)
	
	
	// Test erreur de lecture du repertoire courant
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
	

	// SCAN du répertoire, n = le nombre de fichier et répertoire, n=-1 si erreur lors du scandir
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

		//Permet d'indenter l'affichage
		char * name = namelist[i]->d_name;
		if (namelist[i]->d_type!=4){	// Si on lis un fichier
		
			if (filter(name, option, paramsOption)){	//Si le fichier correspond à la demande de l'utilisateur (flag et paramètres).
				tabulation(tab);
				printf("%s/%s \n", dir,name);	//Alors afficher le chemin
			}
			continue;
			}
										//Si on lis un dossier , On met un peu de couleur
		tabulation(tab);
		printf("\033[0;34m");
		printf("%s/%s \n", dir,name);
		printf("\033[0;37m");
										//Et on fait appel au lsrec dans ce dossier		
		char str1[255];
		strcpy(str1, dir);
		strcat(str1, "/");
		strcat(str1,name);
		tab++;
		lsrec(str1,tab,option, paramsOption);
		tab--;
	}
    free(namelist);    
}
