#include <gtk/gtk.h>
#include <glib.h>
#include "interface.h"

// Define MotSecret globally
const char *MotSecret = NULL;
char motActuel[20];

// Declare label_mot_actuel as a global variable
GtkWidget *label_mot_actuel;

// Function to handle key press event
void on_key_press(GtkWidget *button, gpointer data) {
    // Get the label of the button (the character represented by the button)
    const gchar *keyval = gtk_button_get_label(GTK_BUTTON(button));
    
    // Get the text buffer from the data pointer
    GtkTextBuffer *buffer = GTK_TEXT_BUFFER(data);
    
    // Create an iterator to insert the character at the current cursor position in the text buffer
    GtkTextIter iter;
    gtk_text_buffer_get_iter_at_mark(buffer, &iter, gtk_text_buffer_get_insert(buffer));
    
    // Insert the character into the text buffer at the current cursor position
    gtk_text_buffer_insert(buffer, &iter, keyval, -1);
}


// Function to handle start button click event
void on_start_clicked(GtkWidget *widget, gpointer data) {
    GtkWidget *box_main = GTK_WIDGET(data);
    gtk_widget_destroy(widget);

    GtkWidget *button_easy = gtk_button_new_with_label("Easy");
    GtkWidget *button_medium = gtk_button_new_with_label("Medium");
    GtkWidget *button_hard = gtk_button_new_with_label("Hard");

    g_signal_connect(button_easy, "clicked", G_CALLBACK(on_difficulty_selected), NULL);
    g_signal_connect(button_medium, "clicked", G_CALLBACK(on_difficulty_selected), NULL);
    g_signal_connect(button_hard, "clicked", G_CALLBACK(on_difficulty_selected), NULL);

    gtk_box_pack_start(GTK_BOX(box_main), button_easy, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(box_main), button_medium, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(box_main), button_hard, FALSE, FALSE, 0);

    gtk_widget_show_all(box_main);
}

// Function to handle submit button click event
void on_submit_clicked(GtkWidget *button, gpointer data) {
    GtkTextBuffer *buffer = GTK_TEXT_BUFFER(data);

    GtkTextIter start, end;
    gtk_text_buffer_get_bounds(buffer, &start, &end);
    gchar *text = gtk_text_buffer_get_text(buffer, &start, &end, FALSE);

    gchar *uppercaseMotSecret = g_ascii_strup(MotSecret, -1);

    gchar *current_character = text;

    // Update motActuel
    int taille = strlen(MotSecret);
    for (int i = 0; i < taille; i++) {
        if (motActuel[i] == '\0') {
            motActuel[i] = '_';  // Initialize to underscore if not guessed yet
        }
    }
    motActuel[taille] = '\0';

    gboolean found = FALSE;

    while (*current_character != '\0') {
        gchar character = g_ascii_toupper(*current_character);
        g_print("Character submitted: %c\n", character);

        g_print("Uppercase MotSecret: %s\n", uppercaseMotSecret);

        for (int i = 0; i < taille; i++) {
            if (uppercaseMotSecret[i] == character) {
                motActuel[i] = character;  // Update motActuel with guessed character
                found = TRUE;
            }
        }

        if (found) {
            g_print("Character matches one character of MotSecret.\n \n");
        } else {
            g_print("Character does not match any character of MotSecret.\n \n");
        }

        current_character++;
    }

    // Update the label with the current state of motActuel
    gtk_label_set_text(GTK_LABEL(label_mot_actuel), motActuel);
    
        // Check if the player has guessed the entire word
    if (strcmp(motActuel, uppercaseMotSecret) == 0) {
        // Display congratulatory message
        GtkWidget *dialog = gtk_message_dialog_new(NULL,
                                                    GTK_DIALOG_MODAL,
                                                    GTK_MESSAGE_INFO,
                                                    GTK_BUTTONS_OK,
                                                    "Congratulations! You guessed the word!");
        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);
    }

    // Clear the text buffer
    gtk_text_buffer_set_text(buffer, "", -1);

    g_free(text);
    g_free(uppercaseMotSecret);
}




// Function to handle difficulty selection
void on_difficulty_selected(GtkWidget *button, gpointer data) {
    // Create the virtual keyboard window
    GtkWidget *keyboard_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(keyboard_window), "Hangman Game");
    gtk_window_set_default_size(GTK_WINDOW(keyboard_window), 600, 400);

    // Connect the "destroy" signal to close the window
    g_signal_connect(keyboard_window, "destroy", G_CALLBACK(gtk_window_close), NULL);

    // Create text view and buffer for user input
    GtkWidget *text_view = gtk_text_view_new();
    GtkTextBuffer *buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(text_view));

    // Create the grid for the virtual keyboard
    GtkWidget *keyboard_grid = gtk_grid_new();
    gchar *keys[] = {
        "Q", "W", "E", "R", "T", "Y", "U", "I", "O", "P",
        "A", "S", "D", "F", "G", "H", "J", "K", "L",
        "Z", "X", "C", "V", "B", "N", "M"};

    for (int i = 0; i < G_N_ELEMENTS(keys); i++) {
        GtkWidget *button = gtk_button_new_with_label(keys[i]);
        g_signal_connect(button, "clicked", G_CALLBACK(on_key_press), buffer);
        gtk_grid_attach(GTK_GRID(keyboard_grid), button, i % 10, i / 10, 1, 1);
    }

    // Create a vertical box to pack widgets
    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_container_add(GTK_CONTAINER(keyboard_window), vbox);

    // Create a label for welcome message
    GtkWidget *label = gtk_label_new("Welcome to the Hangman Game!");
    gtk_widget_set_halign(label, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(label, GTK_ALIGN_START);
    gtk_box_pack_start(GTK_BOX(vbox), label, FALSE, FALSE, 0);

    // Get the difficulty level from the selected button
    const gchar *diff = gtk_button_get_label(GTK_BUTTON(button));
    g_print("Difficulty Level Selected: %s\n", diff);

    // Create a label for displaying the difficulty level
    GtkWidget *labeld = gtk_label_new(diff);
    gtk_widget_set_h
    align(labeld, GTK_ALIGN_CENTER);
    gtk_box_pack_start(GTK_BOX(vbox), labeld, FALSE, FALSE, 0);
    
        // Create label_mot_actuel only once during initialization
    label_mot_actuel = gtk_label_new(motActuel);
    gtk_box_pack_start(GTK_BOX(vbox), label_mot_actuel, FALSE, FALSE, 0);

    // Pack text view and keyboard grid
    gtk_box_pack_start(GTK_BOX(vbox), text_view, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), keyboard_grid, TRUE, TRUE, 0);

    // Create the "Submit" button
    GtkWidget *button_submit = gtk_button_new_with_label("Submit");
    g_signal_connect(button_submit, "clicked", G_CALLBACK(on_submit_clicked), buffer);
    gtk_box_pack_start(GTK_BOX(vbox), button_submit, FALSE, FALSE, 0);

    // Create the "Exit" button
    GtkWidget *button_exit = gtk_button_new_with_label("Exit");
    g_signal_connect(button_exit, "clicked", G_CALLBACK(gtk_window_close), keyboard_window);
    gtk_box_pack_end(GTK_BOX(vbox), button_exit, FALSE, FALSE, 0);

    // Show all widgets in the keyboard window
    gtk_widget_show_all(keyboard_window);
}


// Function to initialize and run the game interface
int game_interface(const char *Mot) {
    GtkWidget *window;
    GtkWidget *button_start;
    GtkWidget *button_exit;
    GtkWidget *frame;
    GtkWidget *label_title;
    GtkWidget *box_main;

    gtk_init(NULL, NULL);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Hangman Game");
    gtk_container_set_border_width(GTK_CONTAINER(window), 10);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);
    gtk_window_set_default_size(GTK_WINDOW(window), 600, 400);

    frame = gtk_frame_new(NULL);
    gtk_container_add(GTK_CONTAINER(window), frame);

    box_main = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_container_add(GTK_CONTAINER(frame), box_main);

    label_title = gtk_label_new("Hangman game :) ");
    gtk_widget_set_halign(label_title, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(label_title, GTK_ALIGN_CENTER);
    gtk_widget_set_margin_top(label_title, 20);
    gtk_widget_set_margin_bottom(label_title, 20);
    gtk_widget_set_name(label_title, "title");
    gtk_box_pack_start(GTK_BOX(box_main), label_title, FALSE, FALSE, 0);

    button_start = gtk_button_new_with_label("Start");
    g_signal_connect(button_start, "clicked", G_CALLBACK(on_start_clicked), box_main);
    gtk_box_pack_start(GTK_BOX(box_main), button_start, FALSE, FALSE, 0);

    // Create the "Exit" button
    button_exit = gtk_button_new_with_label("Exit");
    g_signal_connect(button_exit, "clicked", G_CALLBACK(gtk_main_quit), NULL);
    gtk_box_pack_end(GTK_BOX(box_main), button_exit, FALSE, FALSE, 0);

    GtkCssProvider *css_provider = gtk_css_provider_new();
    gtk_css_provider_load_from_data(css_provider,
                                    "#title {"
                                    "   background-color: #3498db;"
                                    "   color: #ffffff;"
                                    "   border-radius: 10px;"
                                    "   padding: 10px;"
                                    "   font-size: 24px;"
                                    "}",
                                    -1, NULL);
    gtk_style_context_add_provider_for_screen(gdk_screen_get_default(),
                                              GTK_STYLE_PROVIDER(css_provider),
                                              GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);

    gtk_widget_show_all(window);

    // Assign Mot to MotSecret
    MotSecret = g_strdup(Mot);

    gtk_main();

    // Free MotSecret after game interface exits
    g_free((gpointer) MotSecret);

    return 0;
}
