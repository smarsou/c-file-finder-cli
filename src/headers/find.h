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

void find(char *dir,  char *option, char * paramsOption[]);
void findall(char *dir,char* taillePattern);
void findallDate(char* s,char * taillePattern);

#endif
