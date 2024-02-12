#define MAX(x, y) (((x) > (y)) ? (x) : (y)) // Macro to find maximum of two numbers

// Construct Empty Tree
TArbre arbreConsVide()
{
    return NULL; // Returns NULL for an empty tree
}

// Returns true if the tree is empty
bool arbreEstVide(TArbre a)
{
    if (a == NULL)
    {
        return true; // Returns true if the tree is empty
    }
    return false; // Returns false if the tree is not empty
}

// Construct Node
TArbre arbreCons(char caractere, int entier, TArbre filsGauche, TArbre filsDroit)
{
    // Allocates memory for a new node and initializes its fields
    TArbre a = (Noeud *)malloc(sizeof(Noeud));
    a->caractere = caractere;
    a->nbrOccurrence = entier;
    a->filsGauche = filsGauche;
    a->filsDroit = filsDroit;
    return a; // Returns the newly created node
}

// Returns the character of the root
char arbreRacineLettre(TArbre a)
{
    if (!arbreEstVide(a))
    {
        return a->caractere; // Returns the character of the root if the tree is not empty
    }
    return '\0'; // Returns null character if the tree is empty
}

// Returns Left Child
TArbre noeudFilsGauche(TArbre a)
{
    if (a != NULL)
    {
        return a->filsGauche; // Returns the left child if it exists
    }
    return NULL; // Returns NULL if the left child does not exist
}

// Returns Right Child
TArbre noeudFilsDroit(TArbre a)
{
    if (a != NULL)
    {
        return a->filsDroit; // Returns the right child if it exists
    }
    return NULL; // Returns NULL if the right child does not exist
}

// Allows to delete the tree
void arbreSuppr(TArbre *noeud)
{
    if (*noeud != NULL)
    {
        arbreSuppr(&((*noeud)->filsDroit)); // Deletes the right subtree recursively
        arbreSuppr(&((*noeud)->filsGauche)); // Deletes the left subtree recursively
        free(*noeud); // Frees memory for the current node
        *noeud = NULL; // Sets the pointer to NULL
    }
}

// Returns the height of the tree
int hauteurArbre(TArbre a)
{
    if (a != NULL)
    {
        return 1 + MAX(hauteurArbre(a->filsGauche), hauteurArbre(a->filsDroit)); // Calculates and returns the height of the tree recursively
    }
    return -1; // Returns -1 if the tree is empty
}

void afficherNoeuds(TArbre noeud, int espace)
{
    if (noeud != NULL)
    {
    	int i;
        for (i = 0; i < espace; i++)
            printf("-");

        if (noeud->caractere != '\0')
        {
            
            if(noeud->caractere == ' '){
                printf("NULL\n"); // Prints "NULL" if the character is a space
            }else{
                printf("%c\n", noeud->caractere); // Prints the character if it is not a space
            }
        }
        else
        {
            printf("\\0\n"); // Prints "\0" if the character is null
        }
        if (noeud->filsGauche != NULL)
            printf("[G]"); // Prints "[G]" for Left Child
        afficherNoeuds(noeud->filsGauche, espace + 1); // Recursively prints the left subtree
        if (noeud->filsDroit != NULL)
            printf("[D ]"); // Prints "[D]" for Right Child
        afficherNoeuds(noeud->filsDroit, espace + 1); // Recursively prints the right subtree
    }
}

// Allows to display the tree
void afficherArbre(TArbre a)
{
    if (a != NULL)
    {
        printf("\n*******************************TREE*******************************\n");
        printf("\nHeight of the tree : %i\n\n", hauteurArbre(a)); // Prints the height of the tree
        printf("[R ]"); // Prints "[R]" for Root
        afficherNoeuds(a, 1); // Calls the function to print nodes recursively
        printf("\n/*******************************TREE*******************************/\n");
    }
}

// Trie Character Search
TArbre rechercheCaractereTrie(TArbre a, char caractere) {
    // Base case: empty tree or character found
    if (arbreEstVide(a) || a->caractere == caractere) {
        return a; // Returns the node if the character is found or if the tree is empty
    }

    // If the character is smaller than the root character, search in the left subtree
    if (caractere != a->caractere) {
        return rechercheCaractereTrie(a->filsGauche, caractere);
    }
    // Otherwise, search in the right subtree
    return rechercheCaractereTrie(a->filsDroit, caractere);
}

