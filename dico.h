#ifndef DEF_DICTIONNAIRE
#define DEF_DICTIONNAIRE

#define TAILLE_MAX 255

// Structure definition for storing a word
typedef struct {
    char mot[TAILLE_MAX]; // Array to store the word
} Mot;

// Function prototypes

// Opens the dictionary file for reading
int ouvrirDictionnaire(const char *filename);

// Opens the dictionary file for writing (append mode)
int ouvrirDictionnaireEcriture(const char *filename);

// Searches for a word in the dictionary file
int chercherMotDico(const char *word, const char *filename);

// Removes a word from the dictionary file
int supprimerMotDico(const char *word, const char *filename);

// Picks a random word from the dictionary file
int piocherMot(char *motPioche);

// Generates a random number within a specified range
int nombreAleatoire(int nombreMax);

// Displays all words in the dictionary
void afficherMotsDictionnaire();

// Inserts a word into the dictionary tree
void dicoInsererMot(char *mot, TArbre *arbre);

// Inserts a word into the dictionary tree (helper function)
void insererMot(char *mot, TArbre *noeud);

// Manages the dictionary (adds, searches, deletes words)
void gestionDuDico(TArbre *arbre);

#endif

