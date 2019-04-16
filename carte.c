#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <MLV/MLV_all.h>

#include "carte.h"
#include "fichier.h"


void creerFenetre() {
    MLV_create_window("PVC", "PVC", TAILLE_X, TAILLE_Y);
    MLV_actualise_window();
}


int comparerVisite(const void *a, const void *b) {
    Visite **v1, **v2;
    v1 = (Visite **)a;
    v2 = (Visite **)b;

    return (int)((*v1)->longueur - (*v2)->longueur);
}

void trierVisite(Visite *v[], int taille) {
    assert(NULL != v);

    qsort(v, taille, sizeof(v[0]), &comparerVisite);
}

void chercherMeilleureVisite(const Visite *ref, char *nom) {
    FILE *fichier = NULL;
    Visite *tab_v[K], *tab_v2[K];
    int i;
    double meilleur_lg, lg;
    MLV_Keyboard_button touche;

    assert(NULL != ref);

    for (i = 0; i < K; i++) {
        tab_v[i] = allouerVisite(ref->nb_villes);
        tab_v2[i] = allouerVisite(ref->nb_villes);

        genererVisiteAlea(tab_v[i], ref);
    }
    
    trierVisite(tab_v, K);
    meilleur_lg = tab_v[0]->longueur;

    creerFenetre();

    while (1) {
        construirePopulation(tab_v, tab_v2, ref, ALPHA, BETA, GAMMA);
        trierVisite(tab_v2, K);
        lg = tab_v2[0]->longueur;

        if ( lg < meilleur_lg ) {
            meilleur_lg = lg;

            afficherCarte(tab_v2[0]);
            if ( ouvrirPVC(&fichier, nom) ) {
                ecrireFichier(tab_v2[0], fichier);
                fclose(fichier);
            }
        }

        for (i = 0; i < K; i++)
            copierVisite(tab_v2[i], tab_v[i]);


        MLV_get_event(
            &touche, NULL, NULL,
            NULL, NULL,
            NULL, NULL,
            NULL, NULL
        );

        if ( touche == MLV_KEYBOARD_RETURN )
            break;
    }
    printf("La longueur de la meilleure visite : %f\n", meilleur_lg);

    for (i = 0; i < K; i++) {
        libererVisite(tab_v[i]);
        libererVisite(tab_v2[i]);
    }

    MLV_free_window();
}

void construirePopulation(Visite *tab_v[], Visite *tab_v2[], const Visite *ref, int alpha, int beta, int gamma) {
    int a, b, c;

    assert(NULL != ref);
    assert(NULL != tab_v);
    assert(NULL != tab_v2);

    for (a = 0; a < alpha; a++) {
        muterVisite(tab_v[a], tab_v2[a]);
    }

    for (b = 0; b < beta; b++) {
        copierVisite(tab_v[b], tab_v2[a + b]);
    }

    for (c = 0; c < gamma; c++) {
        genererVisiteAlea(tab_v2[a + b + c], ref);
    }
}

void afficherCarte(const Visite *v) {
    int i;

    assert(NULL != v);

    MLV_clear_window(MLV_COLOR_BLACK);

    for (i = 0; i < v->nb_villes - 1; i++) {
        MLV_draw_line(
            v->ville[i].x, v->ville[i].y,
            v->ville[i + 1].x, v->ville[i + 1].y,
            MLV_COLOR_GREEN
        );

        MLV_draw_filled_circle(
            v->ville[i].x, v->ville[i].y,
            2, MLV_COLOR_RED
        );

        MLV_draw_filled_circle(
            v->ville[i + 1].x, v->ville[i + 1].y,
            2, MLV_COLOR_RED
        );
    }
    MLV_actualise_window();
}


int lancerPVC(char *nom, int nb) {
    Visite *ref;
    FILE *fichier = NULL;

    if ( !ouvrirFichier(&fichier, nom) ) {
        creerFichierVilles(nb, nom);
        ouvrirFichier(&fichier, nom);
    }

    ref = creerPremVisite(fichier);
    if (NULL == ref)
        return 0;
    calculerLongueur(ref);
    fclose(fichier);

    chercherMeilleureVisite(ref, nom);
    return 1;
}