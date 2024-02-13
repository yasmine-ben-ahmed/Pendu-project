#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include "arbre.h"  // Header file for the tree structure
#include "arbre.c"  // Source file for the tree functions
#include "dico.h"   // Header file for the dictionary operations
#include "dico.c"   // Source file for the dictionary functions
#include "pendu.c"  // Source file for the hangman game logic
#include "pendu.h"  // Header file for the hangman game functions

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

    gestionDuDico(&arbre); // Manage the dictionary (add, delete, search words)

    genererMotSecret(&arbre); // Generate a secret word for the hangman game

    jeuxDePendu(arbre); // Play the hangman game

    arbreSuppr(&arbre); // Free memory allocated for the tree nodes

    return 0; // Return success code
}

