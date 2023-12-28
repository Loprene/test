#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "tmp.h"
#include "test.h"


long taille_fichier(char * nom) {
  FILE * f  = fopen(nom, "rb");
  long r = 0;
  if (f) {
    fseek(f, 0, SEEK_END);
    r = ftell(f);
    fclose(f);
  }
  return r;
}


char *lecture(char *nom) 
{
    FILE *file = fopen(nom, "r");
    if (file == NULL) {
        fprintf(stderr, "Erreur d'ouverture du fichier %s\n", nom);
        return NULL;
    }

    long taille = taille_fichier(nom);
    if (taille == -1) {
        fclose(file);
        return NULL;
    }

    char *texte = (char *)malloc(taille + 1);
    if (texte == NULL) {
        fprintf(stderr, "Erreur d'allocation de mémoire\n");
        fclose(file);
        return NULL;
    }

    if (fread(texte, 1, taille, file) != taille) {
        fprintf(stderr, "Erreur de lecture du fichier %s\n", nom);
        fclose(file);
        free(texte);
        return NULL;
    }

    texte[taille] = '\0';

    fclose(file);

    return texte;
}

BEGIN_TEST_GROUP(exo2)


TEST(LECTURE1, "") {
    char * texte;

    
    texte = lecture("essai.txt");

    REQUIRE( NULL != texte);
    CHECK( (unsigned)taille_fichier("essai.txt") == strlen(texte));     

    texte = lecture("pastrouve.txt");
    REQUIRE( NULL == texte);

    free(texte);
}

END_TEST_GROUP(exo2)


int main() {
    RUN_TEST_GROUP(exo2); 
    return 0;
}


