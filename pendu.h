#ifndef DEF_PENDU
#define DEF_PENDU

// Maximum length for input strings
#define TAILLE_MAX 255   

// Function prototypes
char lireCaractere();                      // Function to read a character from the user
void lireLigne(char* mot);                  // Function to read a line of text from the user
void genererMotSecret(TArbre *Mdico);       // Function to generate a secret word for the game
void displayHangman(int tries);             // Function to display the Hangman figure based on the number of tries
int jeuxDePendu(TArbre trie);               // Function to play the Hangman game

#endif

