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
    int n = scandir(dir, &namelist, 0, alphasort);
	if (n==-1){ 
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
		strcpy(str1, "./");
		strcat(str1,name);
		tab++;
		lsrec(str1,tab);
		tab--;
	}
    free(namelist);    
}

int main(int argc, const char *argv[])
{
	// _ls(".");
    lsrec(".", 0);
	return EXIT_SUCCESS;
}