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

const char *MotS;
// Declare the game_interface function
int game_interface(GtkWidget *window, const char *MotS);

int main() {

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
    
    MotS = genererMotSecret(&arbre);
     // Afficher le mot secret
     printf("\n \t \t ((Secret word: %s))\n", MotS);
    
    //jeuxDePendu(arbre);
    
    /********************************************************************************/
    // Initialize GTK
    gtk_init(NULL, NULL);

    // Create a GTK window
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Hangman Game");
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    
    // Call the game_interface function with the window pointer
    game_interface(window,MotS);

    // Show the window
    gtk_widget_show_all(window);

    // Run the GTK main loop
    gtk_main();
    /**********************************************************************************/ 
       	    
    arbreSuppr(&arbre);
    
return 0;    
}
