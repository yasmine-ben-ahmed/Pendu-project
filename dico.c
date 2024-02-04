#include <stdio.h>

FILE *dico; // Déclaration d'une variable globale pour stocker le pointeur vers le fichier du dictionnaire
char buffer[20];

// Fonction pour ouvrir le fichier du dictionnaire
int ouvrirDictionnaire(const char *filename) {
    dico = fopen("Dictionnaire.txt", "r");
    if (dico == NULL) {
        printf("\nUnable to load word dictionary");
        return 0; // Retourne 0 si l'ouverture du fichier a échoué
    }
    return 1; // Retourne 1 si l'ouverture du fichier a réussi
}


int nombreAleatoire(int nombreMax)
{
    return (rand() % nombreMax+1);
}


int piocherMot(char *motPioche)
{
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
	   
    ouvrirDictionnaire("Dictionnaire.txt");
    
    if (dico == NULL) {
        printf("Error: dictionary file not open\n");
    }

    // Tableau dynamique pour stocker les mots
    Mot *mots = NULL;
    size_t tailleMots = 0;
    char ligne[TAILLE_MAX];

    // Lisez chaque ligne du fichier et stockez le mot dans le tableau
    while (fgets(ligne, TAILLE_MAX, dico) != NULL) {
        size_t len = strlen(ligne);

        // Supprimez le saut de ligne à la fin du mot
        if (len > 0 && ligne[len - 1] == '\n') {
            ligne[len - 1] = '\0';
        }

        // Ajoutez le mot au tableau dynamique
        Mot nouveauMot;
        strcpy(nouveauMot.mot, ligne);

        tailleMots++;
        mots = realloc(mots, tailleMots * sizeof(Mot));
        mots[tailleMots - 1] = nouveauMot;
    }

    fclose(dico);
    
    printf("\n\n______________________________________________________________________________________\n");
printf("**************************************************************************************\n");
printf("\n**************!! Algorithm Project First Engineering ISI Ariana !!********************\n");
printf("______________________________________________________________________________________\n");
printf("______________________________________________________________________________________\n\n");

// Display all words in the array
printf("\n********DICTIONARY********\n");
printf("\nWords from the dictionary:\n");
for (size_t i = 0; i < tailleMots; i++) {
    printf("[%ld] %s\n", i + 1, mots[i].mot);
}
printf("\n/********DICTIONARY********/\n");

// Free the memory used by the array
free(mots);
}

//gestion dico

void insererMot(char *mot, TArbre *noeud)
{
    if (*noeud != NULL)
    {
        if (mot[0] != '\0') //pas fin de mot
        {
            if ((*noeud)->caractere == mot[0])
            {
                mot++; // effacer premier caractere
                insererMot(mot, &((*noeud)->filsGauche));//descendre gauche
            }
            else
            {
                if((*noeud)->caractere > mot[0]){ //ordre alphabetique
                        TArbre n = arbreCons(mot[0], 0, NULL, *noeud);
                        mot++;
                        *noeud = n;
                        insererMot(mot, &((*noeud)->filsGauche));
                }else{
                    if ((*noeud)->filsDroit != NULL)//descendre droite
                    {
                        insererMot(mot, &((*noeud)->filsDroit));
                  
                    }
                    else //caractere n'existe pas
                    {
                        (*noeud)->filsDroit = arbreCons(mot[0], 0, NULL, NULL);
                        insererMot(mot, &(*noeud)->filsDroit);
                    }
                }
            }
        }
        else if (mot[0] == '\0' && (*noeud)->caractere != '\0')//cas particulier
        {
                    TArbre n = arbreCons('\0', 1, NULL, *noeud); 
                    *noeud = n;
        }
        else if (mot[0] == '\0' && (*noeud)->caractere == '\0') //fin de mot
        {
            (*noeud)->nbrOccurrence++;
        }
    }
    else
    {
        if (mot[0] != '\0')
        {
            *noeud = arbreCons(mot[0], 0, NULL, NULL);
            mot++;
            insererMot(mot, &((*noeud)->filsGauche));
        }
        else
        {
            *noeud = arbreCons('\0', 1, NULL, NULL);
        }
    }
}

//Permet d'ajouter un mot 
void dicoInsererMot(char *mot, TArbre*arbre)
{
    if (strlen(mot) > 0)
    {
        if (*arbre == NULL)
            *arbre = arbreConsVide();

        insererMot(mot, arbre);

    }
}






















