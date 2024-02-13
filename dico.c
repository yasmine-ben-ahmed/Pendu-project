#include <stdio.h>

FILE *dico; // Global variable declaration to store the pointer to the dictionary file
char buffer[20];

// Function to open the dictionary file
int ouvrirDictionnaire(const char *filename) {
    dico = fopen("Dictionnaire.txt", "r");
    if (dico == NULL) {
        printf("\nUnable to load word dictionary");
        return 0; // Returns 0 if the file opening failed
    }
    return 1; // Returns 1 if the file opening succeeded
}

// Function to open the dictionary file in write mode
int ouvrirDictionnaireEcriture(const char *filename) {
    dico = fopen(filename, "a"); // Opens the file in append mode ("a")
    if (dico == NULL) {
        printf("\nImpossible d'ouvrir le dictionnaire de mots en écriture");
        return 0; // Returns 0 if the file opening failed
    }
    return 1; // Returns 1 if the file opening succeeded
}



// Function to search for a word in the dictionary file
int chercherMotDico(const char *word, const char *filename) {
    FILE *dico = fopen(filename, "r");
    if (dico == NULL) {
        printf("Error: dictionary file not open\n");
        return 0;
    }

    // Iterate through the words in the dictionary file
    while (fscanf(dico, "%s", buffer) == 1) {
        if (strcmp(buffer, word) == 0) { // Check if the word matches
            fclose(dico);
            return 1; // Word found
        }
    }

    fclose(dico);
    return 0; // Word not found
}


// Function to remove a word from the dictionary file
int supprimerMotDico(const char *word, const char *filename) {
    // Check if the word exists in the dictionary
    if (!chercherMotDico(word, filename)) {
        printf("\n =====> Your word '%s' does not exist in the dictionary.\n", word);
        return 0; // Word not found, no need to proceed further
    }

    // Open the dictionary file for reading
    FILE *dico = fopen(filename, "r");
    if (dico == NULL) {
        printf("Error: dictionary file not open\n");
        return 0;
    }

    // Create a temporary file to write the updated dictionary
    FILE *temp = fopen("temp.txt", "w");
    if (temp == NULL) {
        printf("Error: unable to create temporary file\n");
        fclose(dico);
        return 0;
    }
    
    // Iterate through the words in the dictionary file
    while (fscanf(dico, "%s", buffer) == 1) {
        if (strcmp(buffer, word) != 0) { // Check if the word doesn't match
            fprintf(temp, "%s\n", buffer); // Write the word to the temporary file
        }
    }

    fclose(dico);
    fclose(temp);

    // Remove the original dictionary file
    remove(filename);

    // Rename the temporary file to the original dictionary file
    rename("temp.txt", filename);

    return 1; // Word found and deleted successfully
}

// Function to generate a random number between 0 and nombreMax (inclusive)
int nombreAleatoire(int nombreMax) {
    return (rand() % nombreMax + 1);
}

// Function to randomly select a word from the dictionary file
int piocherMot(char *motPioche) {
    ouvrirDictionnaire("Dictionnaire.txt");
    if (dico == NULL) {
        printf("Error: dictionary file not open\n");
        return 0;
    }

    // Count the number of words in the file
    int nombreMots = 0;
    while (fscanf(dico, "%s", motPioche) == 1) {
        nombreMots++;
    }

    // Generate a random number between 0 and (nombreMots - 1)
    srand(time(NULL));
    int numMotChoisi = rand() % nombreMots;

    // Reset the file pointer to the beginning of the file
    rewind(dico);

    // Read the file until the chosen word
    for (int i = 0; i < numMotChoisi; i++) {
        if (fscanf(dico, "%s", motPioche) != 1) {
            printf("Error retrieving the secret word.\n");

            fclose(dico);
            return 0;
        }
    }

    fclose(dico);
    return 1;
}

// Function to display all words from the dictionary
void afficherMotsDictionnaire() {
    // Open the dictionary file
    ouvrirDictionnaire("Dictionnaire.txt");
    
    if (dico == NULL) {
        printf("Error: dictionary file not open\n");
    }

    // Dynamic array to store the words
    Mot *mots = NULL;
    size_t tailleMots = 0;
    char ligne[TAILLE_MAX];

    // Read each line from the file and store the word in the array
    while (fgets(ligne, TAILLE_MAX, dico) != NULL) {
        size_t len = strlen(ligne);

        // Remove the newline character at the end of the word
        if (len > 0 && ligne[len - 1] == '\n') {
            ligne[len - 1] = '\0';
        }

        // Add the word to the dynamic array
        Mot nouveauMot;
        strcpy(nouveauMot.mot, ligne);

        tailleMots++;
        mots = realloc(mots, tailleMots * sizeof(Mot));
        mots[tailleMots - 1] = nouveauMot;
    }

    fclose(dico);
    
    // Display all words in the array
    printf("\n\n______________________________________________________________________________________\n");
    printf("**************************************************************************************\n");
    printf("\n**************!! Algorithm Project First Engineering ISI Ariana !!********************\n");
    printf("______________________________________________________________________________________\n");
    printf("______________________________________________________________________________________\n\n");

    printf("\n********DICTIONARY********\n");
    printf("\nWords from the dictionary:\n");
    for (size_t i = 0; i < tailleMots; i++) {
        printf("[%ld] %s\n", i + 1, mots[i].mot);
    }
    printf("\n/********DICTIONARY********/\n");

    // Free the memory used by the array
    free(mots);
}


// Function to insert a word into the dictionary tree
void insererMot(char *mot, TArbre *noeud) {
    if (*noeud != NULL) {
        if (mot[0] != '\0') { // Not end of word
            if ((*noeud)->caractere == mot[0]) {
                mot++; // Remove first character
                insererMot(mot, &((*noeud)->filsGauche)); // Move left
            } else {
                if ((*noeud)->caractere > mot[0]) { // Alphabetical order
                    TArbre n = arbreCons(mot[0], 0, NULL, *noeud);
                    mot++;
                    *noeud = n;
                    insererMot(mot, &((*noeud)->filsGauche));
                } else {
                    if ((*noeud)->filsDroit != NULL) // Move right
                        insererMot(mot, &((*noeud)->filsDroit));
                    else // Character does not exist
                    {
                        (*noeud)->filsDroit = arbreCons(mot[0], 0, NULL, NULL);
                        insererMot(mot, &(*noeud)->filsDroit);
                    }
                }
            }
        } else if (mot[0] == '\0' && (*noeud)->caractere != '\0') { // Special case
            TArbre n = arbreCons('\0', 1, NULL, *noeud);
            *noeud = n;
        } else if (mot[0] == '\0' && (*noeud)->caractere == '\0') // End of word
        {
            (*noeud)->nbrOccurrence++;
        }
    } else {
        if (mot[0] != '\0') {
            *noeud = arbreCons(mot[0], 0, NULL, NULL);
            mot++;
            insererMot(mot, &((*noeud)->filsGauche));
        } else {
            *noeud = arbreCons('\0', 1, NULL, NULL);
        }
    }
}

// Function to add a word to the dictionary
void dicoInsererMot(char *mot, TArbre *arbre) {
    if (strlen(mot) > 0) {
        if (*arbre == NULL)
            *arbre = arbreConsVide();

        insererMot(mot, arbre);
    }
}



// Function to manage the dictionary
void gestionDuDico(TArbre *arbre) {
    char word[100]; // Assuming the word will not exceed 100 characters
    int choice;

    printf("_________________________________________________\n\n");
    printf("Do you want to manage the dictionary? \n Type 1 for yes or 0 to continue to the game\n");
    scanf(" %d", &choice);

    if (choice == 1) {
        printf("**************Dictionary management**************\n\n");
        printf("Type 1 to add a word to the dictionary\n");
        printf("Type 2 to search for a word in the dictionary\n");
        printf("Type 3 to delete a word from the dictionary\n");
        scanf(" %d", &choice);

        switch (choice) {
            case 1:
                // Ask the user to enter a word
                printf("\nEnter a word you want to add to the dictionary: ");

                // Read the input word from the user
                scanf(" %s", word);

                // Call the function to insert the word into the dictionary tree
                dicoInsererMot(word, arbre);

                // Open the dictionary file in append mode to add the word
                if (!chercherMotDico(word, "Dictionnaire.txt")) {
                    FILE *dico = fopen("Dictionnaire.txt", "a");
                    if (dico == NULL) {
                        printf("Error: dictionary file not open\n");
                    } else {
                        // Write the word to the dictionary file
                        fprintf(dico, "%s\n", word);
                        fclose(dico); // Close the file after writing
                    }

                    printf("=====> Your word '%s' was successfully added to the dictionary !!!\n", word);
                } else {
                    printf("\n=====> Your word '%s' already exists in the dictionary !!!\n", word);
                }
                break;

            case 2:
                // Ask the user to enter a word
                printf("\nEnter a word you want to search in the dictionary: ");

                // Read the input word from the user
                scanf(" %s", word);

                // Add the logic to search for a word in the dictionary
                if (!chercherMotDico(word, "Dictionnaire.txt")) {
                    printf("\n=====> Your word '%s' does not exist in the dictionary !!!\n", word);
                } else {
                    printf("\n=====> Your word '%s' exists in the dictionary !!!\n", word);
                }
                break;

            case 3:
                // Add the logic to delete a word from the dictionary
                // Ask the user to enter a word
                printf("\nEnter a word you want to delete from the dictionary: ");

                // Read the input word from the user
                scanf(" %s", word);

                if (supprimerMotDico(word, "Dictionnaire.txt")) {
                    printf("\n=====> Your word '%s' was successfully deleted from the dictionary.\n", word);
                }
                break;

            default:
                printf("Invalid choice! (Hangman game soon...)\n");
                break;
        }
    } else if (choice == 0) {
        printf("Continuing to the game Hangman...\n");
    } else {
        printf("Invalid choice! (Hangman game soon...)\n");
    }
}
