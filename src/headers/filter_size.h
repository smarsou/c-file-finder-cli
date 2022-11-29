#ifndef FILTERSIZE
#define FILTERSIZE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <regex.h>

off_t FileSize(const char *filename);
int filterSize(long double tailleDuFichier,char *taillePattern);

#endif
