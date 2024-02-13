#ifndef INTERFACE_H
#define INTERFACE_H

#include <gtk/gtk.h>

// Header guard to prevent multiple inclusion of the header file

// Function declarations
void on_key_press(GtkWidget *button, gpointer data); // Function to handle key press event
void on_start_clicked(GtkWidget *widget, gpointer data); // Function to handle start button click event
void on_submit_clicked(GtkWidget *button, gpointer data); // Function to handle submit button click event
void on_difficulty_selected(GtkWidget *button, gpointer data); // Function to handle difficulty selection
int game_interface(const char *Mot); // Function to initialize and run the game interface

#endif /* INTERFACE_H */

