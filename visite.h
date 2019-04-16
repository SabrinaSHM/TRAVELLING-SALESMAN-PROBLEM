#ifndef __VISITE__
#define __VISITE__

#include "ville.h"

#define K 128
#define ALPHA 64
#define BETA 32
#define GAMMA 32


typedef struct {
    Ville *ville;
    int nb_villes;
    double longueur;
} Visite;


int rand_a_b(int a, int b);

Visite* allouerVisite(int nb_villes);
Visite* creerPremVisite(FILE *fichier);
void libererVisite(Visite *v);

void genererVisiteAlea(Visite *v, const Visite *ref);

void muterVisite(Visite *v, Visite *nouv);
void copierVisite(Visite *src, Visite *cible);

#endif