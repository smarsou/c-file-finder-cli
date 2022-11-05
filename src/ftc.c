#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int isElement(char** list,char* element)
{
    /*
    printf("\nsizeof list =%ld\n",sizeof(list));
    printf("\nnumber of elts list =%ld\n",sizeof(list)/sizeof(list[0]));
    printf("\nsizeof list0 =%ld\n",sizeof(list[0]));*/
    for (int i = 0; i < 12; i++)
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
    int count;

    printf("\nCommand-line arguments:\n");
    for( count = 0; count < argc; count++ )
        printf("  argv[%d]   %s\n", count, argv[count]);

    //vérifier que c'est bien une option existante
    char* Options[12]={"-test","-name","-date","-size","-mime","-ctc","-dir","-color","-perm","-links","-threads","-ou"};
    if (isElement(Options,argv[2]))
    {
        printf("\n------------------------------ok-------------------\n");
    }
    else
    {
        printf("\nOption non reconnue\n");
        return 0;
    }
    
    if (!strcmp(argv[1],"-test"))
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

    return 0;
}
