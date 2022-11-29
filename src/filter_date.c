#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <errno.h>
#include "headers/lsRec.h"
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include "headers/filter_date.h"

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
