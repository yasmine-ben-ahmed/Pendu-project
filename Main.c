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

const char *MotSecret;


int main() {
    TArbre arbre; // Declare a tree variable
    arbre = arbreConsVide(); // Initialize the tree as empty

    afficherMotsDictionnaire(); // Display the words in the dictionary

    FILE *fichierMots = fopen("Dictionnaire.txt", "r"); // Open the dictionary file in read mode

    if (fichierMots == NULL) {
        fprintf(stderr, "Unable to open the file Dictionary.txt.\n"); // Print error message if file cannot be opened
        return 1; // Return error code
    }

    char ligne[TAILLE_MAX]; // Declare a character array to store a line from the file

    while (fgets(ligne, TAILLE_MAX, fichierMots) != NULL) { // Read each line from the file
        size_t len = strlen(ligne);
        if (len > 0 && ligne[len - 1] == '\n') {
            ligne[len - 1] = '\0'; // Remove newline character if present
        }

        dicoInsererMot(ligne, &arbre); // Insert the word into the dictionary tree
    }

    fclose(fichierMots); // Close the file

    afficherArbre(arbre); // Display the tree containing the dictionary words
    
    MotSecret = genererMotSecret(&arbre);
     // Afficher le mot secret
     printf("\n \t \t ((Secret word: %s))\n", MotSecret);
    
    game_interface(MotSecret);

       	    
    arbreSuppr(&arbre); // Free memory allocated for the tree nodes

    return 0; // Return success code
       
}
