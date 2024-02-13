#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


char motActuel[20];
TArbre trie;

// Function to read a character from the user
char lireCaractere() {
    char caractere = 0;
    // Read the character
    scanf(" %c", &caractere); // Notice the space before %c to skip whitespace characters

    // Clear the input buffer
    while (getchar() != '\n'); // Keep reading characters until encountering a newline

    // Si l'utilisateur a tapé '1', retourner une valeur spéciale pour indiquer la sortie
    if (caractere == '0') {
        return -1;  // Return a special value to indicate exit
    }
    
    return caractere;
}

void lireLigne(char* mot) {
    int i = 0;

    while ((mot[i] = getchar()) != '\n') {
        // Utilisez isdigit pour vérifier si le caractère est un chiffre
        if (!isdigit(mot[i])) {
            printf("\t \t!!!! Please enter a number.\n");
            // Clear the input buffer to prevent issues with subsequent inputs
            while (getchar() != '\n');
            i = 0;  // Réinitialiser l'index pour recommencer la saisie
        } else {
            // Convertir le caractère en majuscule
            mot[i] = toupper(mot[i]);
            i++;
        }
    }
    mot[i] = '\0';
}


char* genererMotSecret(TArbre *Mdico) {
    static char MotSecret[20]; 
    *Mdico = arbreConsVide();

    // Pick a single random word
    if (selectword(MotSecret) == 1) {
        printf("_________________________________________________\n\n");
        // Afficher le mot secret
       // printf("\n \t \t ((Secret word: %s))\n", MotSecret);

        // Insert the secret word into the dictionary tree (if necessary)
        dicoInsererMot(MotSecret, Mdico);
    } else {
        printf("Error retrieving the secret word.\n\n");
    }
    
    return MotSecret;
}


