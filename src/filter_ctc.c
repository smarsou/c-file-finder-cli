#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <errno.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "headers/filter_ctc.h"
#include "headers/filter_size.h"
#include "headers/filter_name.h"

int filterCtc(char * path, char *pattern){
    FILE * file = fopen(path,"r");
    if ( file == NULL){
        perror("Error file not found");
        // fprintf(stderr, "Error file not found: %s \n", path);
        return 0;
    }
    
    off_t size = FileSize(path);

    // Transformer le fichier en une seule chaine de caractère
    char * fileAsAchar = malloc(size*4);
    char c;
    int i = -1;
    while((c = fgetc(file)) != EOF ){
        fileAsAchar[i++]=c;
    }
    pclose(file);
    if (!evaluateRegex(fileAsAchar, pattern)){
        return 1;
    }else{
        return 0;
    }
}
