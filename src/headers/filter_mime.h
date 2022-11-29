#ifndef FILTERMIME
#define FILTERMIME
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "MegaMimes.h"

int filterMime(const char *path, char *mime);

#endif
