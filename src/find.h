#ifndef FIND
#define FIND
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <errno.h>
#include "find.h"
#include <sys/stat.h>
#include <sys/types.h>

void find(char *dir,  char *option, char * paramsOption[]);
int filter(char *option, char * paramsOption[],struct dirent *namelistEl);
int filterSize(long double tailleDuFichier,char *taillePattern);
int filterName(char *name, char *pattern);
off_t FileSize(const char *filename);
void findall(char *dir,char* taillePattern);

#endif
