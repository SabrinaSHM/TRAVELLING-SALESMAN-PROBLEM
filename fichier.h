#ifndef __FICHIER__
#define __FICHIER__

#include "ville.h"
#include "visite.h"
 

int ouvrirFichier(FILE **fichier, char s[]);
int ouvrirPVC(FILE **fichier, char s[]);

int creerFichierVilles(int nb_villes, char *nom);
void ecrireFichier(const Visite *v, FILE *fichier);


#endif