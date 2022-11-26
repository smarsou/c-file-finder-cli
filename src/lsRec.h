#ifndef LS_REC
#define LS_REC
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <errno.h>
#include "lsRec.h"
#include <sys/stat.h>
#include <sys/types.h>

void tabulation(int tab);
void lsrec(char *dir, int tab);
void ls(char *dir, int tab);
void find(char *dir,  char *option, char * paramsOption[]);
int filter(char *option, char * paramsOption[],struct dirent *namelistEl);
int filterSize(long double tailleDuFichier,char *taillePattern);
int filterName(char *name, char *pattern);
off_t FileSize(const char *filename);
int isElement(char** list,char* element);
void findall(char *dir,char* taillePattern);

#endif
