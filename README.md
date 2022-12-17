# Projet Système

### Membres
- Youssef Trabelsi G32...
- Soulaïman Marsou G32 ...

### Librairies externe utilisés
- Megamimes - pour les types mime

# Travail réalisé
## Principale
- Q.1  ✅ - Youssef 
- Q.2  ✅ - Soulaïman 
- Q.3  ✅ - Youssef 
- Q.4  ✅ - Youssef
- Q.5  ✅ - Youssef 
- Q.6  ✅ - Soulaïman
- Q.7  ✅ - Soulaïman 
- Q.8  ✅ grep - Soulaïman
- Q.9  ✅ - Soulaïman 
- Q.10 ✅ - Youssef / Soulaïman
- Q.11 ✅ - Youssef / Soulaïman

## Extensions

- 🔴 color
- ✅ recherche par date par mots clés
- ✅ recherche selon le type de permission 
- 🔴 -link
- ✅ 'OU'
- 🔴 UTF-8
- 🔴 multithreads
- 🔴 ftc sous windows
- 🔴 Trouver le code du chat

# Annexes

## Gestion de plusieurs flags
### Première idée (pas terminée)

        int n = nombre de flag possible

        int tableau2[n] = {0, 0, 0, ... , 0};

        --> Vérifier si argv[1] existe et est bien un chemin

        int i=0
        char * currentflag = NULL
        char params[n][argc];

        Pour 2<=i<= argc:
            Si arg est un flag
                Si currentflag != NULL:
                    Tester la validité des paramètres du flag précédent
                        tableau[flag.index]=1 ou -1
                currentflag = arg
            Si arg n'est pas un flag
                Ajouter arg à la liste des paramètres
