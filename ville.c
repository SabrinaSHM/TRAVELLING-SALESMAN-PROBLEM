#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "ville.h"


int estCharValide(char c) {
    if (('a' <= c && c <= 'z') || ('A' <= c && c <= 'Z') || c == '-' || ('0' <= c && c <= '9'))
        return 1;

    return 0;
}

int estNomValide(char nom[]) {
    int i;
    assert(nom != NULL);

    for(i = 0; nom[i] != '\0'; i++){
        if( !estCharValide(nom[i]) )
            return 0;
    }
    return 1;
}