#include <stdio.h>

FILE *dico; // Déclaration d'une variable globale pour stocker le pointeur vers le fichier du dictionnaire
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


// Function to generate a random number between 0 and nombreMax (inclusive)
int nombreAleatoire(int nombreMax) {
    return (rand() % nombreMax + 1);
}

// Function to randomly select a word from the dictionary file
int selectword(char *motPioche) {
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
