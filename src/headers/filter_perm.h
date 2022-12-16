#ifndef FILTERPERM
#define FILTERPERM
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <regex.h>

long int fileperm(char * filename);
int filterperm(long int permDuFichier,char * PermPattern);

#endif
