#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "ville.h"
#include "visite.h"
#include "fichier.h"
#include "calculs.h"
#include "carte.h"


int main(int argc, char *argv[]) {
    srand(time(NULL));

    if (argc != 3) {
        printf("Exécutez sous la forme : ./PVC (Nom du fichier) (Nombre de villes)\n");
        return 1;
    }

    if (argv[1] == NULL) {
        printf("Aucun nom de fichier n'est entré, réessayez.\n");
        return 1;
    }
    else {
        if ( NULL == argv[2] || (10 > atoi(argv[2]) || atoi(argv[2]) > 1000) ) {
            printf("Le nombre de villes entré est invalide.\n");
            return 1;
        }
        else
            if ( !lancerPVC(argv[1], atoi(argv[2])) ) {
                printf("Fichier non valide\n");
                return 1;
            }
    }
    
    return 0;
}