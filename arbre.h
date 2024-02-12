#ifndef DEF_ARBRE
#define DEF_ARBRE

// Definition of the structure representing a node in the tree
typedef struct Noeud Noeud;
struct Noeud
{
    char caractere;             // Character stored in the node
    struct Noeud *filsDroit;    // Pointer to the right child node
    struct Noeud *filsGauche;   // Pointer to the left child node
    int nbrOccurrence;          // Number of occurrences of the character
};

// Definition of the pointer type for the tree node
typedef Noeud * TArbre;

// Definition of the structure representing the tree
typedef struct Arbre Arbre;
struct Arbre
{
    struct Noeud *racine;       // Pointer to the root node of the tree
};

// Function prototypes

// Constructs an empty tree
TArbre arbreConsVide();

// Checks if the tree is empty
bool arbreEstVide(TArbre a);

// Constructs a node with the given character, occurrence count, and children nodes
TArbre arbreCons(char caractere, int entier, TArbre filsGauche, TArbre filsDroite);

// Returns the character stored in the root node of the tree
char arbreRacineLettre(TArbre a);

// Returns the left child of the given node
TArbre arbreFilsGauche(TArbre a);

// Returns the right child of the given node
TArbre arbreFilsDroit(TArbre a);

// Deletes the entire tree
void arbreSuppr(TArbre *arbre);

// Displays the tree structure
void afficherArbre(TArbre a);

// Displays the nodes of the tree with proper indentation
void afficherNoeuds(TArbre a, int espace);

// Returns the height of the tree
int hauteurArbre(TArbre a);

// Searches for a character in the tree and returns the corresponding node
TArbre rechercheCaractereTrie(TArbre a, char caractere);

#endif

