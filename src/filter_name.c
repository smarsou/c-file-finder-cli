#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <regex.h>
#include "headers/filter_name.h"

int evaluateRegex(char *name, char *pattern){
    //int value;
    regex_t reegex;
    regcomp( &reegex, pattern, 0);
    return regexec( &reegex, name,0, NULL, 0);
}

int filterName(char *name, char *pattern){
	return !evaluateRegex(name, pattern); //Si le nom est le même que celui passé en paramètre d'option
}
