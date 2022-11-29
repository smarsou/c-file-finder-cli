#ifndef FILTERNAME
#define FILTERNAME
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <regex.h>

int evaluateRegex(char *name, char *pattern);
int filterName(char *name, char *pattern);

#endif
