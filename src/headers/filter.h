#ifndef FILTER
#define FILTER
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <regex.h>
#include "filter_mime.h"
#include "filter_name.h"

int filter(char *option, char * paramsOption[],struct dirent *namelistEl, char* dir);

#endif
