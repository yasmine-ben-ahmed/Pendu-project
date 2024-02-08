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


// Function to get the directory of the executable file
char *get_executable_directory(const char *argv0) {
    char *last_slash = strrchr(argv0, '/');
    if (last_slash) {
        int dir_length = last_slash - argv0 + 1;
        char *directory = malloc(dir_length + 1);
        if (directory) { // Check if malloc succeeded
            strncpy(directory, argv0, dir_length);
            directory[dir_length] = '\0';
            return directory;
        } else {
            // Handle malloc failure
            return NULL;
        }
    }
    return NULL;
}


int main(int argc, char *argv[]) {
    // Print the program name
    printf("Program name: %s\n", argv[0]);

    // Loop through and print the command-line arguments
    for (int i = 1; i < argc; i++) {
        printf("Argument %d: %s\n", i, argv[i]);
    }
    
        // Get the directory of the executable
    char *executable_directory = get_executable_directory(argv[0]);
    if (!executable_directory) {
        printf("Error: Unable to determine executable directory.\n");
        return 1;
    }

    // Print the executable directory
    printf("Executable directory: %s\n", executable_directory);

    // Free the allocated memory for executable_directory
    free(executable_directory);

/******************************************************/


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
