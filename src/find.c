#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "headers/find.h"
#include "headers/filter.h"


void find(char *dir, char *option, char * paramsOption[]){
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
            
			if (filterSize(FileSize(str1),taillePattern))
			{
				printf("%s\n",str1);
			}
			
        }
    }
    closedir(rep);
}


void findallDate(char* s,char * taillePattern)
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
			if (strcmp(lecture->d_name, ".")!=0 && strcmp(lecture->d_name, "..")!=0 && lecture->d_name[0]!='.')
			{ 
				strcpy(chemin, s);
				strcat(chemin,"/");
				strcat(chemin, lecture->d_name);
				findallDate(chemin,taillePattern);
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
            //printf("\nlecture->d_name=%s \n",lecture->d_name);
			if (filterDate(taillePattern,LastTimeSinceModifiedinSeconds(str1)) && lecture->d_name[0]!='.')
			{
				printf("%s\n",str1);
			}
			
        }
    }
    closedir(rep);
}

void findET(char *s,char * Patterns[2][20],int nb)
{
    //printf("Entered findet\n");
    char chemin[4096];
    struct dirent *lecture;
    DIR *rep;
    rep = opendir(s);
    if (rep == NULL)
    {
        printf("s= %s\n",s);
        printf("rep == null\n");
        perror(s);
        return;
    }
    while ((lecture = readdir(rep))!=NULL)
    {
        if (lecture->d_type == DT_DIR)
        {
			if (strcmp(lecture->d_name, ".")!=0 && strcmp(lecture->d_name, "..")!=0 && lecture->d_name[0]!='.')
			{ 
				strcpy(chemin, s);
				strcat(chemin,"/");
				strcat(chemin, lecture->d_name);
                //printf("recursive call\n");
				findET(chemin,Patterns,nb);
			}
        }
        else
        {
            char str1[255];
            strcpy(str1,s);
            strcat(str1,"/");
            strcat(str1,lecture->d_name);
            int test=1;
            
            
            //printf("Begining filtre\n");
            for (int i=0;i<nb;i++)
            {
                //printf("inside for i=%d\n",i);
                if (!strcmp(Patterns[0][i],"-date"))
                {
                    test=test && filterDate(Patterns[1][i],LastTimeSinceModifiedinSeconds(str1));
                }
                if (!strcmp(Patterns[0][i],"-size"))
                {
                    test=test &&filterSize(FileSize(str1),Patterns[1][i]);
                }
                
                if (!strcmp(Patterns[0][i],"-name"))
                {
                    test=test &&filterName(str1,Patterns[1][i]);
                }

                if (!strcmp(Patterns[0][i],"-dir"))
                {
                    test=test &&filterName(str1,Patterns[1][i]);
                }

                if (!strcmp(Patterns[0][i],"-mime"))
                {
                    test=test &&filterMime(str1,Patterns[1][i]);
                }
                if (!strcmp(Patterns[0][i],"-ctc"))
                {
                    test=test &&filterName(str1,Patterns[1][i]);
                }
            }
            //printf("test= %d\n",test);
            if (test)
            {
                printf("%s\n",str1);
            }
        }
    }
    closedir(rep);
}

void findOU(char *s,char * Patterns[2][20],int nb)
{
    //printf("Entered findet\n");
    char chemin[4096];
    struct dirent *lecture;
    DIR *rep;
    rep = opendir(s);
    if (rep == NULL)
    {
        printf("s= %s\n",s);
        printf("rep == null\n");
        perror(s);
        return;
    }
    while ((lecture = readdir(rep))!=NULL)
    {
        if (lecture->d_type == DT_DIR)
        {
			if (strcmp(lecture->d_name, ".")!=0 && strcmp(lecture->d_name, "..")!=0 && lecture->d_name[0]!='.')
			{ 
				strcpy(chemin, s);
				strcat(chemin,"/");
				strcat(chemin, lecture->d_name);
                //printf("recursive call\n");
				findOU(chemin,Patterns,nb);
			}
        }
        else
        {
            char str1[255];
            strcpy(str1,s);
            strcat(str1,"/");
            strcat(str1,lecture->d_name);
            int test=0;
            
            
            //printf("Begining filtre\n");
            for (int i=0;i<nb;i++)
            {
                //printf("inside for i=%d\n",i);
                if (!strcmp(Patterns[0][i],"-date"))
                {
                    test=test || filterDate(Patterns[1][i],LastTimeSinceModifiedinSeconds(str1));
                }
                if (!strcmp(Patterns[0][i],"-size"))
                {
                    test=test || filterSize(FileSize(str1),Patterns[1][i]);
                }
                
                if (!strcmp(Patterns[0][i],"-name"))
                {
                    test=test || filterName(str1,Patterns[1][i]);
                }

                if (!strcmp(Patterns[0][i],"-dir"))
                {
                    test=test || filterName(str1,Patterns[1][i]);
                }

                if (!strcmp(Patterns[0][i],"-mime"))
                {
                    test=test || filterMime(str1,Patterns[1][i]);
                }
                if (!strcmp(Patterns[0][i],"-ctc"))
                {
                    test=test || filterName(str1,Patterns[1][i]);
                }
            }
            //printf("test= %d\n",test);
            if (test)
            {
                printf("%s\n",str1);
            }
        }
    }
    closedir(rep);
}


long int fileperm(char * filename)
{
    struct stat sb;
    if (stat(filename, &sb) == -1) {
        perror("stat");
        return 1;
    }
    //printf("sb.st_mode & 0777 =%d\n",sb.st_mode & 0777);
    return sb.st_mode & 0777;
}


int filterperm(long int permDuFichier,char * PermPattern)
{

    
    long int pattern = strtol(PermPattern, NULL, 8);

    if (permDuFichier == pattern)
    {
        return 1;
    }
    else
    {
        return 0;
    }

}

void findperm(char *s,char * PermPattern)
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
			if (strcmp(lecture->d_name, ".")!=0 && strcmp(lecture->d_name, "..")!=0 && lecture->d_name[0]!='.')
			{ 
				strcpy(chemin, s);
				strcat(chemin,"/");
				strcat(chemin, lecture->d_name);
				findperm(chemin,PermPattern);
			}
        }
        else
        {
            char str1[255];
            strcpy(str1,s);
            strcat(str1,"/");
            strcat(str1,lecture->d_name);
			if (filterperm(fileperm(str1),PermPattern))
			{
				printf("%s\n",str1);
			}
			
        }
    }
    closedir(rep);
}

