#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "headers/lsRec.h"
#include "headers/find.h"



void test(char* xxxx,char * yyyy)
{
    printf("La valeur du flag %s est %s\n",xxxx,yyyy);
}
int isnotnumber(char  argv)
{
    return argv!='1' && argv!='2' && argv!='3' && argv!='4' && argv!='5' && argv!='6' && argv!='7' && argv!='8' && argv!='9' && argv!='0';
}

int main(int argc,char* argv[])
{
    //Si il n'y a pas d'option
        if (argc == 2){
            ls(argv[1],0,8); //Test du ls récursif sans filtre 
            return EXIT_SUCCESS;
        }

    //Si il y a une option
    //vérifier que c'est bien une option existante
    char* Options[13]={"13","-test","-name","-date","-size","-mime","-ctc","-dir","-color","-perm","-links","-threads","-ou"};
    if (!(isElement(Options,argv[2])))
    {
        printf("\nOption non reconnue\n");
        return EXIT_FAILURE;
    }

    char *OptionsSansParametre[4]={"5","-color","-links","-threads"};
    if (isElement(OptionsSansParametre,argv[2]) )
    {
        if (argv[3]!=NULL)
        {
            printf("\nOption ne prend pas de paramètre\n");
            return EXIT_FAILURE;
        }

    }
    if (argc>4)
    {
        int nbOUET=0;
        char * Patterns[2][20]={{"","","","","","","","","","","","","","","","","","","",""},{"","","","","","","","","","","","","","","","","","","",""}};
        //patterns tableau 2D qui contient les parametres et leurs options correspondants
        Patterns[0][0]=argv[2];
        Patterns[1][0]=argv[3];
        int k=1;
        for (int i=0;i<argc;i++)
        {
            if (!strcmp(argv[i],"ET") || !strcmp(argv[i],"OU"))
            {
                nbOUET++;
            }
        }
        if (nbOUET)
        {
            for (int i = 1; i < argc-2; i++)
            {
                if (!strcmp(argv[i],"ET"))
                {
                    Patterns[0][k]=argv[i+1];
                    //Pattern[0] contient les noms des parametres 
                    if (!strcmp(argv[i+2],"ET"))
                    {
                        Patterns[1][k]="no";
                    }
                    else
                    {
                        //Pattrens contient les options des parametres correspondant si un parametre  est sans option on ajoute on
                        Patterns[1][k]=argv[i+2];
                    }
                    k++;
                }
            }
            if (!strcmp(argv[2],"-ou"))
            {
                Patterns[0][0]=argv[3];
                Patterns[1][0]=argv[4];
                k=1;
                for (int i = 3; i < argc-2; i++)
                {
                    if (!strcmp(argv[i],"ET")||!strcmp(argv[i],"OU"))
                    {
                        Patterns[0][k]=argv[i+1];
                        //Pattern[0] contient les noms des parametres 
                        if (!strcmp(argv[i+2],"ET") ||!strcmp(argv[i+2],"OU"))
                        {
                            Patterns[1][k]="no";
                        }
                        else
                        {
                            //Pattrens contient les options des parametres correspondant si un parametre  est sans option on ajoute on
                            Patterns[1][k]=argv[i+2];
                            
                        }
                        
                        k++;
                    }
                }
                /*for (int i=0;i<nbOUET+1;i++)
                {
                    printf("Patterns[0][%d] = %s\n",i,Patterns[0][i]);
                    printf("Patterns[1][%d] = %s\n",i,Patterns[1][i]);
                }*/
                
                findOU(argv[1],Patterns,nbOUET+1);
                return 1;
            }
            findET(argv[1],Patterns,nbOUET+1);
            return EXIT_SUCCESS;
        }
    }
    //Execution du cas où l'option est -test
    if (!strcmp(argv[2],"-test"))
    {
        if (isElement(Options,argv[3]))
        {
            test(argv[3],argv[4]);
            return 1;
        }
        else
        {
            printf("Le flag %s n'est pas correct",argv[3]);
            return 1;
        }
        
    }
    


    if (!strcmp(argv[2],"-size"))
    {//Vérification du bon paramétrage
        int d=isnotnumber(argv[3][strlen(argv[3])-1]) && argv[3][strlen(argv[3])-1]!='k' && argv[3][strlen(argv[3])-1]!='c' &&argv[3][strlen(argv[3])-1]!='M' &&argv[3][strlen(argv[3])-1]!='G';
        if (argv[3][0]!='+' && argv[3][0]!='-' )
        {
            int c=0;
            for (int i = 0; i < strlen(argv[3])-1; i++)
            {
                
                c=c || isnotnumber(argv[3][i]);

            }
            if (c || d)
            {
                printf("paramétre de -size non reconnu\n");
                return 0;
            } 
        }
        else
        {
            int c=0;
            for (int i = 1; i < strlen(argv[3])-1; i++)
            {
                
                c=c || isnotnumber(argv[3][i]);

            }
            if (d  || c )
            {
                printf("paramétre de -size non reconnu\n");
                return 0;
            }
        }
        
        findall(argv[1],argv[3]);
        return 0;
    }

    if (!strcmp(argv[2],"-date"))
    {//verif de bon param de date
        int d=isnotnumber(argv[3][strlen(argv[3])-1]) && argv[3][strlen(argv[3])-1]!='m' && argv[3][strlen(argv[3])-1]!='h' &&argv[3][strlen(argv[3])-1]!='j';
        if (argv[3][0]!='+' && argv[3][0]!='-' )
        {
            int c=0;
            for (int i = 0; i < strlen(argv[3])-1; i++)
            {
                
                c=c || isnotnumber(argv[3][i]);

            }
            int a=strcmp(argv[3],"now") && strcmp(argv[3],"today") && strcmp(argv[3],"yesterday") && strcmp(argv[3],"this");
            if ((c || d )&& a)
            {
                printf("Paramétre de -date non reconnu\n");
                return 0;
            } 
        }
        else
        {
            int c=0;
            for (int i = 1; i < strlen(argv[3])-1; i++)
            {
                
                c=c || isnotnumber(argv[3][i]);

            }
            printf("c=%d d=%d   case2\n",c,d);
            if (d  || c )
            {
                printf("paramétre de -date non reconnu\n");
                return 0;
            }
        }
        findallDate(argv[1],argv[3]);
        return 1;
    }
    if (!strcasecmp(argv[2],"-perm"))
    {
        int a=isnotnumber(argv[3][strlen(argv[3])-1]);
        int b=isnotnumber(argv[3][0]);
        int c=isnotnumber(argv[3][1]);
        if (a || b || c)
        {
            printf("paramétre de -perm non reconnu\n");
            return 0;
        }
        findperm(argv[1],argv[3]);;
        return 1;
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
        if (argc>5)
        {
            printf("Erreur: Trop de paramètres\n");
            return EXIT_FAILURE;   
        }
        find(argv[1],option,paramsOption);
    }

    if (!strcmp(argv[2],"-dir")){
        if (argc < 4){
            ls(argv[1],0,4);
            return EXIT_SUCCESS;
        }
        if (argc>5)
        {
            printf("Erreur: Trop de paramètres\n");
            return EXIT_FAILURE;   
        }
        find(argv[1],option,paramsOption);
    }

    if (!strcmp(argv[2],"-mime")){
        if (argc < 4){
            printf("Erreur: Spécifiez un type mime\n");
            return EXIT_FAILURE;
        }
        if (argc>5)
        {
            printf("Erreur: Trop de paramètres\n");
            return EXIT_FAILURE;   
        }
        find(argv[1],option,paramsOption);
    }
    if (!strcmp(argv[2],"-ctc")){
        if (argc < 4){
            perror("Erreur: Spécifiez une chaine de caractère\n");
            return EXIT_FAILURE;
        }
        if (argc>4)
        {
            char str2[254];
			strcpy(str2, argv[3]);
			strcat(str2, " ");
            strcat(str2, argv[4]);
            int i;
            for (i = 5; i<argc ; i++)
            {
                strcat(str2, " ");
                strcat(str2, argv[i]);
            }
            paramsOption[0]=str2;
        }
        find(argv[1],option,paramsOption);
    }
    return 1;
    return EXIT_SUCCESS;
}
