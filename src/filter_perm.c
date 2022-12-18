#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <errno.h>
#include "headers/lsRec.h"
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include "headers/filter_perm.h"

long int fileperm(char * filename)
{
    struct stat sb;
    if (stat(filename, &sb) == -1) {
        perror("stat");
        return 1;
    }
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
