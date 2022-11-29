#include <stdio.h>
#include "MegaMimes.h"
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <errno.h>
#include "find.h"
#include <sys/stat.h>
#include <sys/types.h>
#include <regex.h>


int evaluateRegex(char *name, char *pattern){
    int value;
    regex_t reegex;
    regcomp( &reegex, pattern, 0);
    return regexec( &reegex, name,0, NULL, 0);
}

int filterName(char *name, char *pattern){
	if (!evaluateRegex(name, pattern)){ //Si le nom est le même que celui passé en paramètre d'option
			return 1;
		}else{
			return 0;
		}
}
//fonction qui calcule le size d'un fichier
off_t FileSize(const char *filename) {
    struct stat st; 

    if (stat(filename, &st) == 0)
        return st.st_size;

    return -1; 
}


int filterSize(long double tailleDuFichier,char *taillePattern)
{
	int b=taillePattern[strlen(taillePattern)-1]=='c';
	b=b || taillePattern[strlen(taillePattern)-1]=='k' || taillePattern[strlen(taillePattern)-1]=='K' || taillePattern[strlen(taillePattern)-1]=='M';
	if (b)
	{
		//dans le cas où le paramètre d'option se termine par c ou k ou K ou M 
		if ((taillePattern[0]=='-' ||taillePattern[0]=='+'))
		{
			//dans le cas où le paramètre de l'option commence par + ou - 
			char *eptr;
			long double result;
			char * size=malloc(sizeof(strlen(taillePattern)-2));
			for (size_t i = 0; i < strlen(taillePattern)-2; i++)
			{
				size[i]=taillePattern[i+1];
			}
			result = strtold(size, &eptr);
			switch (taillePattern[strlen(taillePattern)-1])
			{
			case 'c':
				break;
			case 'k':
				result=result*1024;
				break;
			case 'M':
				result=result*1024*1024;
				break;
			case 'G':
				result=result*1024*1024*1024;
				break;
			default:
				result=result+(int)taillePattern[strlen(taillePattern)]-48;
				break;
			}
			if (taillePattern[0]=='+')
			{
				if (tailleDuFichier >result)
				{
					return 1;
				}
				else
				{
					return 0;
				}
			}
			else
			{
				if (tailleDuFichier <result &&tailleDuFichier >=0)
				{
					return 1;
				}
				else
				{
					return 0;
				}
			}
		}
		else
		{
			//dans le cas où le paramètre de l'option commence par un entier
			char *eptr;
			long double result;
			char * size=malloc(sizeof(strlen(taillePattern)-1));
			for (size_t i = 0; i < strlen(taillePattern)-1; i++)
			{
				size[i]=taillePattern[i];
			}
			result = strtol(size, &eptr, 10);
			switch (taillePattern[strlen(taillePattern)-1])
			{
			case 'c':
				break;
			case 'k':
				result=result*1024;
				break;
			case 'M':
				result=result*1024*1024;
				break;
			case 'G':
				result=result*1024*1024*1024;
				break;
			default:
				result=result+(int)taillePattern[strlen(taillePattern)]-48;
				break;
			}
			if (tailleDuFichier==result)
			{
				return 1;
			}
			else
			{
				return 0;
			}
			
			
		}
		
	}
	else
	{//dans le cas pas d'unité précise
		if ((taillePattern[0]=='-' ||taillePattern[0]=='+'))
		{
			//dans le cas où le paramètre de l'option commence par + ou - 
			char *eptr;
			long double result;
			char * size=malloc(sizeof(strlen(taillePattern)-1));
			for (size_t i = 0; i < strlen(taillePattern)-1; i++)
			{
				size[i]=taillePattern[i+1];
			}
			result = strtol(size, &eptr, 10);
			if (taillePattern[0]=='+')
			{
				if (tailleDuFichier >result)
				{
					return 1;
				}
				else
				{
					return 0;
				}
			}
			else
			{
				if (tailleDuFichier <result &&tailleDuFichier >=0)
				{
					return 1;
				}
				else
				{
					return 0;
				}
			}
		}
		else
		{
			//dans le cas où le paramètre de l'option commence par un entier
			char *eptr;
			long double result;
			char * size=malloc(sizeof(strlen(taillePattern)));
			for (size_t i = 0; i < strlen(taillePattern); i++)
			{
				size[i]=taillePattern[i];
			}
			result = strtol(size, &eptr, 10);
			if (tailleDuFichier==result)
			{
				return 1;
			}
			else
			{
				return 0;
			}
		}
	}
}

int filterMime(const char *path, char *mime){

    char *mimetype = getMegaMimeType(path);

	if (mimetype==NULL){
		// fprintf(stderr,"Error mime NULL\n");
		return 0;
	}
	// printf("mimetype: %s, mime: %s\n", mimetype, mime);
	char *res = strstr(mimetype, mime);
	if (res){
		// printf("%s\n",res);
		return 1;
	}
	return 0;
}

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

void find(char *dir, char *option, char * paramsOption[]){
    struct dirent *d;
    struct dirent **namelist; // namelist[i] est un pointeur, namelist[i]->d_type est un entier, il permet de savoir si le pointeur nameliste[i] correspond à un répertoire ou un fichier (4 == repertoire, 8 == fichier)
	
	// SCAN du répertoire, n = le nombre de fichier et répertoire, n=-1 si erreur lors du scandir
	int n = scandir(dir, &namelist, 0, alphasort);
	if (n==-1){  // Si y'a une erreur quelconque on skip cette apel récursif
		perror("\nERROR skip this folder\n");
		return;
		}
	
    for (int i =0; i< n; i++){
		
        char letter[]= {namelist[i]->d_name[0], '\0'};
        
        if (!strcmp(letter,".")){
            continue; // Si on tombe sur un dossier ou fichier caché, on ne l'affiche pas.
        }

		//Permet d'indenter l'affichage
		char * name = namelist[i]->d_name;
        // Si on lis un fichier
		if (namelist[i]->d_type!=4){	
			if (filter(option, paramsOption, namelist[i], dir)){	//Si le fichier correspond à la demande de l'utilisateur (flag et paramètres).
				// Traiter les cas "./path/" et "./path"
				size_t taille = strlen(dir);
                if (!(dir[taille-1]=='/')){
                    printf("%s/%s\n", dir,name);
                }else{
					printf("%s%s\n", dir,name);
				}
					
			}
		}
        //Si on lis un dossier
        else{                          
			if (filter(option, paramsOption, namelist[i], dir)){	//Si le dossier correspond à la demande de l'utilisateur (flag et paramètres).
				printf("%s/%s\n", dir,name);	//Alors afficher le chemin
			}
            char str1[255];
            strcpy(str1, dir);
            // Permet de supprimer les doublons de '/'
                size_t taille = strlen(str1);
                if (!(str1[taille-1]=='/')){
                    strcat(str1, "/");
                }
            strcat(str1,name);
            find(str1,option, paramsOption);
        }
	}
    free(namelist);  
}


void findall(char* s,char * taillePattern)
{
    char chemin[4096];
    struct dirent *lecture;
    DIR *rep;
       
    rep = opendir(s);
    if (rep == NULL)
    {
       perror(s);
       return;
    }
    //printf("%s/", s);
    while ((lecture = readdir(rep))!=NULL)
    {
        if (lecture->d_type == DT_DIR)
        {
			if (strcmp(lecture->d_name, ".")!=0 && strcmp(lecture->d_name, "..")!=0)
			{ 
				strcpy(chemin, s);
				strcat(chemin,"/");
				strcat(chemin, lecture->d_name);
				findall(chemin,taillePattern);
			}
        }
        else
        {
            char str1[255];
            strcpy(str1,s);
            strcat(str1,"/");
            strcat(str1,lecture->d_name);
            //printf("%s\n",str1);
            //printf("taille de %s =%lu \n",str1,FileSize(str1));
			if (filterSize(FileSize(str1),taillePattern))
			{
				printf("%s\n",str1);
			}
			
        }
    }
    closedir(rep);
}
