#ifndef __VILLE__
#define __VILLE__

#define T_MAX 200


typedef struct {
    char nom[T_MAX];
    int x;
    int y;
} Ville;


int estCharValide(char c);
int estNomValide(char *nom);

#endif