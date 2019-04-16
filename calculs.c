#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h>

#include "calculs.h"


double hypotenuse(int a, int b) {
    return sqrt( pow(a, 2) + pow(b, 2) );
}

void calculerLongueur(Visite *v) {
    int i, a, b;
    double res = 0;

    for (i = 0; i < v->nb_villes - 1; i++) {
        a = v->ville[i].x - v->ville[i + 1].x;
        b = v->ville[i].y - v->ville[i + 1].y;
        res += hypotenuse(a, b);
    }

    v->longueur = res;
}