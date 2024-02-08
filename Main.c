#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include "arbre.h"
#include "arbre.c"
#include "dico.h"
#include "dico.c"
#include "pendu.c"
#include "pendu.h"
#include "interface.c"
#include "interface.h"
#include <gtk/gtk.h>

//extern const char *MotSecret;
const char *MotSecret;

int main() {

    TArbre arbre;
	   arbre = arbreConsVide();
	
    afficherMotsDictionnaire(); 
      
    FILE *fichierMots = fopen("Dictionnaire.txt", "r");

    if (fichierMots == NULL) {
        fprintf(stderr, "Unable to open the file Dictionary.txt.\n");
        return 1;
    }

    char ligne[TAILLE_MAX];

    while (fgets(ligne, TAILLE_MAX, fichierMots) != NULL) {
        size_t len = strlen(ligne);
        if (len > 0 && ligne[len - 1] == '\n') {
            ligne[len - 1] = '\0';
        }

        dicoInsererMot(ligne, &arbre);
    }

    fclose(fichierMots);
    
    afficherArbre(arbre);
    
    //gestionDuDico(&arbre);
    
    MotSecret = genererMotSecret(&arbre);
     // Afficher le mot secret
     printf("\n \t \t ((Secret word: %s))\n", MotSecret);
    
    //jeuxDePendu(arbre);
    

    game_interface(MotSecret);

       	    
    arbreSuppr(&arbre);
    
return 0;    
}
