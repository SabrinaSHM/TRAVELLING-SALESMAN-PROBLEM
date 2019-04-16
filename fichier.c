#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>


#include "fichier.h"
#include "carte.h"


int ouvrirFichier(FILE **fichier, char s[]) {
    assert(NULL != fichier);

    *fichier = fopen(s, "r");

    if (NULL == *fichier)
        return 0;
    return 1;
}


int ouvrirPVC(FILE **fichier, char s[]) {
    int i;
    char pvc[5] = ".pvc", *nouveau;

    assert(NULL != fichier);

    nouveau = (char *)malloc((sizeof(char) * strlen(s)) + 5);

    if (NULL == nouveau)
        exit(EXIT_FAILURE);

    for (i = 0; s[i] != '.' && s[i] != '\0'; i++)
        nouveau[i] = s[i];
    nouveau[i] = '\0';

    strcat(nouveau, pvc);
    *fichier = fopen(nouveau, "w");

    free(nouveau);
    nouveau = NULL;

    if (NULL == *fichier)
        return 0;
    return 1;
}


int creerFichierVilles(int nb_villes, char *nom) {
    int i;
    FILE *fichier = NULL;

    assert(NULL != nom);
    assert(nb_villes >= 0);

    fichier = fopen(nom, "w+");

    if (NULL == fichier)
        return 0;

    for (i = 0; i < nb_villes; i++) {
        fprintf(fichier, "Ville%d %d %d\n", i, rand()%(TAILLE_X + 1), rand()%(TAILLE_Y + 1));
    }

    fclose(fichier);
    return 1;
}

void ecrireFichier(const Visite *v, FILE *fichier) {
    int i;

    assert(NULL != fichier);
    assert(NULL != v);

    for (i = 0; i < v->nb_villes; i++)
        fprintf(fichier, "%s ", v->ville[i].nom);

    fprintf(fichier, "%f", v->longueur);
}