#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "visite.h"
#include "calculs.h"


int rand_a_b(int a, int b) {
    return rand() % (b - a) + a;
}


Visite* allouerVisite(int nb_villes) {
    Visite *adr = NULL;

    adr = (Visite *)malloc(sizeof(Visite));
    if (NULL == adr)
        exit(EXIT_FAILURE);

    adr->ville = (Ville *)malloc(sizeof(Ville) * nb_villes);
    if (NULL == adr->ville)
        exit(EXIT_FAILURE);

    adr->nb_villes = nb_villes;
    adr->longueur = 0;
    return adr;
}

void libererVisite(Visite *v) {
    assert(NULL != v);

    free(v->ville);
    free(v);
}


Visite* creerPremVisite(FILE *fichier) {
    Visite *v;
    int nb = 0, i = 0;
    char c;

    assert(NULL != fichier);

    while ( (c = fgetc(fichier)) != EOF ) {
        if (c == '\n')
            nb++;
    }

    v = allouerVisite(nb);
    rewind(fichier);

    while ( fscanf(fichier, "%s %d %d", v->ville[i].nom, &(v->ville[i].x), &(v->ville[i].y)) != EOF ) {
        if ( !estNomValide(v->ville[i].nom) )
            return NULL;
        i++;
    }

    return v;
}


void genererVisiteAlea(Visite *v, const Visite *ref) {
    int i, alea;
    Ville tmp;

    assert(NULL != v);
    assert(NULL != ref);

    for (i = 0; i < ref->nb_villes; i++)
        v->ville[i] = ref->ville[i];

    for (i = 0; i < v->nb_villes; i++) {
        alea = rand() % v->nb_villes;

        tmp = v->ville[i];
        v->ville[i] = v->ville[alea];
        v->ville[alea] = tmp;
    }

    calculerLongueur(v);
}


void muterVisite(Visite *v, Visite *nouv) {
    int i, j, l, cpt;
    int nombre = v->nb_villes;
    Ville tmp;

    assert(NULL != v);
    assert(NULL != nouv);

    l = rand_a_b(1, (nombre / 2) + 1);
    i = rand_a_b(1, nombre - (2 * l) + 2);
    j = rand_a_b(i + l, nombre + 2 - l);

    copierVisite(v, nouv);

    for (cpt = 0; cpt < l; cpt++) {
        tmp = nouv->ville[ (i - 1) + cpt ];
        nouv->ville[ (i - 1) + cpt ] = nouv->ville[ (j - 1) + cpt ];
        nouv->ville[ (j - 1) + cpt ] = tmp;
    }

    calculerLongueur(nouv);
}

void copierVisite(Visite *src, Visite *cible) {
    int i;

    assert(NULL != src);
    assert(NULL != cible);

    for (i = 0; i < src->nb_villes; i++) {
        cible->ville[i] = src->ville[i];
    }

    cible->nb_villes = src->nb_villes;
    cible->longueur = src->longueur;
}