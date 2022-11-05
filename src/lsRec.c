#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <errno.h>

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
		exit(EXIT_FAILURE);
	}

	int n = scandir(dir, &namelist, 0, alphasort);
	if (n==-1){  // Si y'a une erreur quelconque
		printf("\nERROR skip this folder\n");
		return;
		}
    for (int i =0; i< n; i++){
        char letter[]= {namelist[i]->d_name[0], '\0'};
        
        if (!strcmp(letter,".")){
            continue; // On n'affiche pas les dossiers et fichiers cachés.
        }
		tabulation(tab);
		char * name = namelist[i]->d_name;
		if (namelist[i]->d_type!=4){
			printf("%s \n", name);
			continue;
		}
		//On met un peu de couleur quand on affiche un dossier
		printf("\033[0;34m");
		printf("%s \n", name);
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

int main(int argc,char *argv[])	
{
	// _ls(".");

    lsrec(argv[1], 0);
	return EXIT_SUCCESS;
}