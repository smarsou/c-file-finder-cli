#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <regex.h>
#include "headers/filter.h"
#include "headers/filter_mime.h"
#include "headers/filter_name.h"

//Fonction de filtre du fichier name en fonction de l'option et des paramètres d'option
int filter(char *option, char * paramsOption[], struct dirent *namelistEl, char *dir){
	if (!strcmp(option,"-name") && namelistEl->d_type==8){ //Si on filtre par nom (-name)
		return filterName(namelistEl->d_name, paramsOption[0]);
	}
    if (!strcmp(option,"-dir") && namelistEl->d_type==4){ //Si on filtre par nom (-dir)
		return filterName(namelistEl->d_name, paramsOption[0]);
	}
    if (!strcmp(option,"-mime") && namelistEl->d_type==8){ //Si on filtre par nom (-dir)
        char str1[255];
            strcpy(str1, dir);
            // Permet de supprimer les doublons de '/'
                size_t taille = strlen(str1);
                if (!(str1[taille-1]=='/')){
                    strcat(str1, "/");
                }
            strcat(str1,namelistEl->d_name);
		return filterMime(str1, paramsOption[0]);
	}
    return 0;
	/*if (!strcmp(option,"-size")){ //Si on filtre par nom (-size)
		/*printf("---------------------\n");
		printf("\nnamelistEl->d_name =%s\n",namelistEl);
		printf("\nsize of namelistEl->d_name =%ld\n",FileSize( namelistEl->d_name));*/
		//return filterSize(FileSize(namelistEl->d_name),paramsOption[0]);
	/*}
	else{
		printf("Option non prise en compte");
		return 0;
	}*/
}

