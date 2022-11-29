#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "headers/filter_size.h"

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
