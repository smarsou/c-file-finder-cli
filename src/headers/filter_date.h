#ifndef FILTERDATE
#define FILTERDATE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>

int filterDate(char * datePattern,double dateLastModif);
double LastTimeSinceModifiedinSeconds(char file_name[]);
void fileLastModified(char file_name[]);

#endif
