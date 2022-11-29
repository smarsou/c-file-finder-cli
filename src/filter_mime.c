#include <stdio.h>
#include "../libs/MegaMimes/src/MegaMimes.h"
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <errno.h>
#include "headers/find.h"
#include <sys/stat.h>
#include <sys/types.h>
#include <regex.h>

int filterMime(const char *path, char *mime){

    char *mimetype = getMegaMimeType(path);

	if (mimetype==NULL){
		// fprintf(stderr,"Error mime NULL\n");
		return 0;
	}
	// printf("mimetype: %s, mime: %s\n", mimetype, mime);
	char *res = strstr(mimetype, mime);
	if (res){
		// printf("%s\n",res);
		return 1;
	}
	return 0;
}
