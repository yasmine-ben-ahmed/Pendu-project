#include <gtk/gtk.h>

void on_start_clicked(GtkWidget *widget, gpointer data) {
    GtkWidget *box_main = GTK_WIDGET(data); // Récupérer le conteneur principal

    // Rechercher et supprimer le bouton "Exit" de la boîte principale
    GList *children = gtk_container_get_children(GTK_CONTAINER(box_main));
    for (GList *iter = children; iter != NULL; iter = g_list_next(iter)) {
        GtkWidget *child = GTK_WIDGET(iter->data);
        if (GTK_IS_BUTTON(child)) {
            gtk_container_remove(GTK_CONTAINER(box_main), child);
        }
    }
    g_list_free(children);

    // Supprimer le bouton "Start" du conteneur principal
    gtk_container_remove(GTK_CONTAINER(box_main), widget);

    // Création des boutons de niveau de difficulté
    GtkWidget *box_difficulty = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    GtkWidget *button_easy = gtk_button_new_with_label("Easy");
    GtkWidget *button_medium = gtk_button_new_with_label("Medium");
    GtkWidget *button_hard = gtk_button_new_with_label("Hard");

    // Ajouter les boutons de difficulté à la boîte de difficulté
    gtk_container_add(GTK_CONTAINER(box_difficulty), button_easy);
    gtk_container_add(GTK_CONTAINER(box_difficulty), button_medium);
    gtk_container_add(GTK_CONTAINER(box_difficulty), button_hard);

    // Création du bouton "Exit" qui restera en dessous des niveaux de difficulté
    GtkWidget *button_exit_below = gtk_button_new_with_label("Exit");
    g_signal_connect(button_exit_below, "clicked", G_CALLBACK(gtk_main_quit), NULL);

    // Ajouter les niveaux de difficulté à la boîte principale
    gtk_container_add(GTK_CONTAINER(box_main), box_difficulty);

    // Ajouter le bouton "Exit" en dessous des niveaux de difficulté
    gtk_container_add(GTK_CONTAINER(box_main), button_exit_below);

    // Afficher les niveaux de difficulté et le bouton "Exit" en dessous des niveaux de difficulté
    gtk_widget_show_all(box_main);
}

int game_interface(GtkWidget *window, const char *Mot) {
    GtkWidget *button_start;
    GtkWidget *button_exit;
    GtkWidget *frame;
    GtkWidget *label_title;
    GtkWidget *box_main;
    GtkWidget *label_word;

    gtk_window_set_default_size(GTK_WINDOW(window), 600, 400);

    frame = gtk_frame_new(NULL);
    gtk_container_add(GTK_CONTAINER(window), frame);

    box_main = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10);
    gtk_container_add(GTK_CONTAINER(frame), box_main);

    label_title = gtk_label_new("Jeu de pendu");
    gtk_widget_set_halign(label_title, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(label_title, GTK_ALIGN_CENTER);
    gtk_widget_set_margin_top(label_title, 20);
    gtk_widget_set_margin_bottom(label_title, 20);
    gtk_widget_set_name(label_title, "title");
    gtk_container_add(GTK_CONTAINER(box_main), label_title);

    // Show the passed word
    char word_text[50];
    sprintf(word_text, "Mot: %s", Mot); // Assuming Mot is an integer
    label_word = gtk_label_new(word_text);
    gtk_widget_set_halign(label_word, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(label_word, GTK_ALIGN_CENTER);
    gtk_widget_set_margin_top(label_word, 20);
    gtk_widget_set_margin_bottom(label_word, 20);
    gtk_container_add(GTK_CONTAINER(box_main), label_word);

    button_start = gtk_button_new_with_label("Start");
    g_signal_connect(button_start, "clicked", G_CALLBACK(on_start_clicked), box_main);
    gtk_container_add(GTK_CONTAINER(box_main), button_start);

    button_exit = gtk_button_new_with_label("Exit");
    g_signal_connect(button_exit, "clicked", G_CALLBACK(gtk_main_quit), NULL);
    gtk_container_add(GTK_CONTAINER(box_main), button_exit);

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

    gtk_main();

    return 0;
}
