#ifndef FIND
#define FIND
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "filter.h"
#include "filter_size.h"
#include "filter_date.h"
#include "filter_perm.h"

void find(char *dir,  char *option, char * paramsOption[]);
void findall(char *dir,char* taillePattern);
void findallDate(char* s,char * taillePattern);
void findET(char *s,char * Patterns[2][20],int nb);
void findOU(char *s,char * Patterns[2][20],int nb);
void findperm(char *s,char * PermPattern);

#endif
