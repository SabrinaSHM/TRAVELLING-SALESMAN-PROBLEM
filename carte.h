#ifndef __GRAPHIQUE__
#define __GRAPHIQUE__

#include "visite.h"
#include "calculs.h"

#define TAILLE_X 800
#define TAILLE_Y 800


void creerFenetre();

int comparerVisite(const void *a, const void *b);
void trierVisite(Visite *v[], int taille);

void chercherMeilleureVisite(const Visite *ref, char *nom);
void construirePopulation(Visite *tab_v[], Visite *tab_v2[], const Visite *ref, int alpha, int beta, int gamma);
void afficherCarte(const Visite *v);

int lancerPVC(char *nom, int nb);

#endif