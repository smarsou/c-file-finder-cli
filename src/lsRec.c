#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <errno.h>
#include "lsRec.h"
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>


//fonction qui verifie si un element est dans une liste (premier element de la liste est sa taille)
int isElement(char** list,char* element)
{
    /*
    printf("\nsizeof list =%ld\n",sizeof(list));
    printf("\nnumber of elts list =%ld\n",sizeof(list)/sizeof(list[0]));
    printf("\nsizeof list0 =%ld\n",sizeof(list[0]));
    */
    int len=atoi(list[0]);
    for (int i = 1; i < len; i++)
    {
        
        /*printf("\nlist[%d] =%s\n",i,list[i]);
        printf("\nelement =%s\n",element);*/
        if (!strcmp(list[i],element))
        {
            return 1;
        }
        
    }
    return 0;
    
}


void tabulation(int tab){
	for (int i=0; i<tab; i++){
		printf("	");
	}
	printf("|");
}

void ls(char* dir, int tab){
	printf("\033[0;34m");
	printf("%s/ \n", dir);
	printf("\033[0;37m");
	lsrec(dir, tab);
}

void lsrec(char *dir, int tab){
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
			tabulation(tab);
			printf("%s/%s \n", dir,name);	//Alors afficher le chemin
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
		lsrec(str1,tab);
		tab--;
	}
    free(namelist);    
}

int filterDate(char * datePattern,double dateLastModif)
{
	if ((datePattern[0]=='-' ||datePattern[0]=='+'))
	{
		//dans le cas où le paramètre de l'option commence par + ou - 
		char *eptr;
		long double result;
		char * size=malloc(sizeof(strlen(datePattern)-2));
		for (size_t i = 0; i < strlen(datePattern)-2; i++)
		{
			size[i]=datePattern[i+1];
		}
		result = strtod(size, &eptr);
		switch (datePattern[strlen(datePattern)-1])
		{
		case 'm':
			result=result*60;
			break;
		case 'h':
			result=result*3600;
			break;
		case 'j':
			result=result*3600*60;
			break;
		default:
			break;
		}
		if (datePattern[0]=='+')
		{
			if (dateLastModif >result)
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
			if (dateLastModif <result &&dateLastModif >=0)
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
		char *eptr;
		long double result;
		char * size=malloc(sizeof(strlen(datePattern)-1));
		for (size_t i = 0; i < strlen(datePattern)-1; i++)
		{
			size[i]=datePattern[i];
		}
		result = strtod(size, &eptr);
		switch (datePattern[strlen(datePattern)-1])
		{
		case 'm':
			result=result*60;
			break;
		case 'h':
			result=result*3600;
			break;
		case 'j':
			result=result*3600*60;
			break;
		default:
			break;
		}
		if (datePattern[0]=='+')
		{
			if (dateLastModif >result)
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
			if (dateLastModif <result &&dateLastModif >=0)
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

void fileLastModified(char file_name[])
{
	time_t rawtime;
	struct tm * timeinfo;
	time ( &rawtime );
	timeinfo = localtime ( &rawtime );
	printf ( "Current local time and date: %s", asctime (timeinfo) );


    char t[ 100 ] = "";
    struct stat b;
    if (!stat(file_name, &b)) 
    {
        strftime(t, 100, "%d/%m/%Y %H:%M:%S", localtime( &b.st_mtime));
        printf("\nLast modified date and time = %s\n", t);
    } 
    else 
    {
        printf("Cannot display the time.\n");
    }
}



double LastTimeSinceModifiedinSeconds(char file_name[])
{
	//get local time
	char buf[255] = {0};
    
    time_t rawtime = time(NULL);
    
    if (rawtime == -1) {
        
        puts("The time() function failed");
        return 1;
    }
    struct tm *ptm = localtime(&rawtime);
    
    time_t loc=mktime(ptm);

    char t[100] = "";
    struct stat b;
    struct tm * modifie=localtime( &b.st_mtime);
    if (!stat(file_name, &b)) 
	{
        time_t modified=mktime(localtime( &b.st_mtime));
        return difftime(loc,modified);
    } 
    else 
    {
    printf("Cannot display the time.\n");
    return EXIT_FAILURE;
    }
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
			if (strcmp(lecture->d_name, ".")!=0 && strcmp(lecture->d_name, "..")!=0)
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
			if (filterDate(taillePattern,LastTimeSinceModifiedinSeconds(str1)))
			{
				printf("%s\n",str1);
			}
			
        }
    }
    closedir(rep);
}


