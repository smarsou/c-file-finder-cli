#ifndef LS_REC
#define LS_REC

void tabulation(int tab);
void lsrec(char *dir, int tab);
void ls(char *dir, int tab);
void find(char *dir,  char *option, char * paramsOption[]);
int filter(char *option, char * paramsOption[],struct dirent *namelistEl);
int filterSize(int tailleDuFichier,char *taillePattern);
int filterName(char *name, char *pattern);
long int FileSize(char file[]);
int isElement(char** list,char* element);
void findall(char *dir,char* taillePattern);

#endif
