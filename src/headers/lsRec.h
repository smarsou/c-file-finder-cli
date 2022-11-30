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
#include <time.h>

void tabulation(int tab);
void lsrec(char *dir, int tab, int type);
void ls(char *dir, int tab, int type);
int isElement(char** list,char* element);

#endif
