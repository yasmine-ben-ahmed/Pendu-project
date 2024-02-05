#ifndef INTERFACE_H
#define INTERFACE_H

#include <gtk/gtk.h>



// Function declarations
void game_logic();
void on_key_press(GtkWidget *button, gpointer data);
void on_submit_clicked(GtkWidget *button, gpointer data);
void on_difficulty_selected(GtkWidget *button, gpointer data);
void on_start_clicked(GtkWidget *widget, gpointer data);
int game_interface( const char *Mot);

#endif /* INTERFACE_H */

