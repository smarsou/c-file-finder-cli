#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lsRec.h"

int isElement(char** list,char* element)
{
    /*
    printf("\nsizeof list =%ld\n",sizeof(list));
    printf("\nnumber of elts list =%ld\n",sizeof(list)/sizeof(list[0]));
    printf("\nsizeof list0 =%ld\n",sizeof(list[0]));
    */
    int len=atoi(list[0]);
    for (int i = 1; i < len; i++)
    {
        
        /*printf("\nlist[%d] =%s\n",i,list[i]);
        printf("\nelement =%s\n",element);*/
        if (!strcmp(list[i],element))
        {
            return 1;
        }
        
    }
    return 0;
    
}

void test(char* xxxx,char * yyyy)
{
    printf("la valeur du flag %s est %s\n",xxxx,yyyy);
}


int main(int argc,char* argv[],char ** envp)
{
    //printf infos 
    //printf("\033[0;33m");
    /*printf("\nCommand-line arguments:\n");
    for( int count = 0; count < argc; count++ )
        printf("  argv[%d]   %s\n", count, argv[count]);*/
    //printf("  argc   %d\n", argc);
    //printf("\n\033[0;37m");
    //Si il n'y a pas d'option
        if (argc == 2){
            lsrec(argv[1],0,"NULL", NULL); //Test du ls récursif sans filtre 
            return EXIT_SUCCESS;
        }

    //Si il y a une option
        //vérifier que c'est bien une option existante
        char* Options[13]={"13","-test","-name","-date","-size","-mime","-ctc","-dir","-color","-perm","-links","-threads","-ou"};
        if (isElement(Options,argv[2]))
        {
            //printf("\n------------------------------Option reconnue-------------------\n");
        }
        else
        {
            printf("\nOption non reconnue\n");
            return EXIT_FAILURE;
        }

        char *OptionsSansParametre[5]={"5","-ctc","-color","-links","-threads"};
        if (isElement(OptionsSansParametre,argv[2]) )
        {
            if (argv[3]!=NULL)
            {
                printf("\nOption ne prend pas de paramètre\n");
                return EXIT_FAILURE;
            }

        }
        //vérifier le bon paramétrage de -size
        if (!strcmp(argv[2],"-size") && ((argv[3][0]=='+' || argv[3][0]=='-')))
        {
            int index=1;
            char* Numbers[11]={"11","0","1","2","3","4","5","6","7","8","9"};
            char  p[1];
            p[0]=argv[3][index];
            while (isElement(Numbers,p))
            {
                p[0]=argv[3][index];
                printf("\n argv[3][%d] =%c\n",index,argv[3][index]);
                index++;
            }
            char* Taille[5]={"5","c","k","K","M"};
            if (isElement(Taille,p))
            {
                printf("\n------------------------------Paramètre de l'option -size reconnu-------------------\n");
            }
            else
            {
                printf("\n argv[3][index] =%d\n",argv[3][index]);
                printf("\nParamètre non reconnu\n");
                return EXIT_FAILURE;
            }
            
            
        }
        


        //Définir les variables interéssantes pour filter le lsrec
        char * option = argv[2];
        char * paramsOption[argc-3];
        for (int i =0; i<argc-3; i++){
            paramsOption[i] = argv[i+3];
        }
        //Execution du cas où l'option est -name
        if (!strcmp(argv[2],"-name")){
            if (argc < 4){
                printf("Erreur: Spécifiez un nom de fichier\n");
                return EXIT_FAILURE;
            }
            lsrec(argv[1],0,option,paramsOption);
        }

        //Execution du cas où l'option est -test
        if (!strcmp(argv[2],"-test"))
        {
            test(argv[2],argv[3]);
        }

    /*
    ET/OU param -option [param]
    date param  int+h/m/j
    size param  +/- int+ c/k/M/G
    mime param  types de fichiers text/html  text
    dir param   -option [param]/NULL
    perm param int (permission)
    */

    return EXIT_SUCCESS;
}
