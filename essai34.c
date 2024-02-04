#include <gtk/gtk.h>

// Fonction de rappel pour les touches du clavier virtuel
void on_key_press(GtkWidget *button, gpointer data) {
    // Récupérer le label du bouton (la valeur de la touche)
    const gchar *keyval = gtk_button_get_label(GTK_BUTTON(button));

    // Récupérer le champ de texte cible
    GtkTextBuffer *buffer = GTK_TEXT_BUFFER(data);

    // Récupérer la position du curseur
    GtkTextIter iter;
    gtk_text_buffer_get_iter_at_mark(buffer, &iter, gtk_text_buffer_get_insert(buffer));

    // Insérer la valeur de la touche à la position du curseur
    gtk_text_buffer_insert(buffer, &iter, keyval, -1);
}

// Fonction de rappel pour les boutons de niveau de difficulté
void on_difficulty_selected(GtkWidget *button, gpointer data) {
    // Création de la fenêtre pour le clavier virtuel
    GtkWidget *keyboard_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(keyboard_window), "Virtual Keyboard");
    gtk_window_set_default_size(GTK_WINDOW(keyboard_window), 300, 200);
    g_signal_connect(keyboard_window, "destroy", G_CALLBACK(gtk_widget_destroy), NULL);

    // Création du champ de texte pour simuler la saisie
    GtkWidget *text_view = gtk_text_view_new();
    GtkTextBuffer *buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(text_view));

    // Création du clavier virtuel
    GtkWidget *keyboard_grid = gtk_grid_new();
    gchar *keys[] = { "1", "2", "3", "4", "5", "6", "7", "8", "9", "0",
                      "Q", "W", "E", "R", "T", "Y", "U", "I", "O", "P",
                      "A", "S", "D", "F", "G", "H", "J", "K", "L",
                      "Z", "X", "C", "V", "B", "N", "M" };

    // Ajout des boutons au clavier virtuel
    for (int i = 0; i < G_N_ELEMENTS(keys); i++) {
        GtkWidget *button = gtk_button_new_with_label(keys[i]);
        g_signal_connect(button, "clicked", G_CALLBACK(on_key_press), buffer);
        gtk_grid_attach(GTK_GRID(keyboard_grid), button, i % 10, i / 10, 1, 1);
    }

    // Organisation de l'interface utilisateur
    GtkWidget *vbox = gtk_box_new(GTK_ORIENTATION_VERTICAL, 5);
    gtk_container_add(GTK_CONTAINER(keyboard_window), vbox);
    gtk_box_pack_start(GTK_BOX(vbox), text_view, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vbox), keyboard_grid, TRUE, TRUE, 0);

    // Affichage de la fenêtre du clavier virtuel
    gtk_widget_show_all(keyboard_window);
}

// Fonction de rappel pour le clic sur le bouton "Start"
void on_start_clicked(GtkWidget *widget, gpointer data) {
    // Récupérer le conteneur principal
    GtkWidget *box_main = GTK_WIDGET(data);

    // Supprimer le bouton "Start"
    gtk_widget_destroy(widget);

    // Création des boutons de niveau de difficulté
    GtkWidget *button_easy = gtk_button_new_with_label("Easy");
    GtkWidget *button_medium = gtk_button_new_with_label("Medium");
    GtkWidget *button_hard = gtk_button_new_with_label("Hard");

    // Connexion des signaux des boutons de difficulté
    g_signal_connect(button_easy, "clicked", G_CALLBACK(on_difficulty_selected), NULL);
    g_signal_connect(button_medium, "clicked", G_CALLBACK(on_difficulty_selected), NULL);
    g_signal_connect(button_hard, "clicked", G_CALLBACK(on_difficulty_selected), NULL);

    // Ajouter le bouton "Exit" à la fin
    GtkWidget *button_exit = gtk_button_new_with_label("Exit");
    g_signal_connect(button_exit, "clicked", G_CALLBACK(gtk_main_quit), NULL);

    // Ajouter les boutons de difficulté et le bouton "Exit" à la boîte principale
    gtk_box_pack_start(GTK_BOX(box_main), button_easy, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(box_main), button_medium, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(box_main), button_hard, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(box_main), button_exit, FALSE, FALSE, 0);

    // Afficher les boutons de difficulté et le bouton "Exit"
    gtk_widget_show_all(box_main);
}

int main(int argc, char *argv[]) {
    GtkWidget *window;
    GtkWidget *button_start;
    GtkWidget *button_exit;
    GtkWidget *frame;
    GtkWidget *label_title;
    GtkWidget *box_main;

    // Initialisation de GTK
    gtk_init(&argc, &argv);

    // Création de la fenêtre principale
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Interface GTK");
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // Définir la taille par défaut de la fenêtre
    gtk_window_set_default_size(GTK_WINDOW(window), 600, 400);

    // Création d'un cadre pour organiser les éléments
    frame = gtk_frame_new(NULL);
    gtk_container_add(GTK_CONTAINER(window), frame);

    // Ajoutez un conteneur principal pour organiser les éléments
    box_main = gtk_box_new(GTK_ORIENTATION_VERTICAL, 10); // 10 est l'espacement entre les enfants du conteneur
    gtk_container_add(GTK_CONTAINER(frame), box_main);

    label_title = gtk_label_new("Jeu de pendu");
    gtk_widget_set_halign(label_title, GTK_ALIGN_CENTER);
    gtk_widget_set_valign(label_title, GTK_ALIGN_CENTER);
    gtk_widget_set_margin_top(label_title, 20);
    gtk_widget_set_margin_bottom(label_title, 20);
    gtk_widget_set_name(label_title, "title");
    gtk_box_pack_start(GTK_BOX(box_main), label_title, FALSE, FALSE, 0);

    // Création du bouton "Start"
    button_start = gtk_button_new_with_label("Start");
    g_signal_connect(button_start, "clicked", G_CALLBACK(on_start_clicked), box_main);
    gtk_box_pack_start(GTK_BOX(box_main), button_start, FALSE, FALSE, 0);

    // Création du bouton "Exit"
    button_exit = gtk_button_new_with_label("Exit");
    g_signal_connect(button_exit, "clicked", G_CALLBACK(gtk_main_quit), NULL);

    // Ajouter le bouton "Exit" à la fin
    gtk_box_pack_end(GTK_BOX(box_main), button_exit, FALSE, FALSE, 0);

    // Chargement du fournisseur de CSS
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

    // Affichage de tous les éléments de la fenêtre
    gtk_widget_show_all(window);

    // Lancement de la boucle principale GTK
    gtk_main();

    return 0;
}

