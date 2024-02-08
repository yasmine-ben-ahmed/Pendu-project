#include <gtk/gtk.h>

void display_image(const char *image_path) {
    GtkWidget *window;
    GtkWidget *image;

    // Initialize GTK
    gtk_init(NULL, NULL);

    // Create a new top-level window
    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Image Viewer");
    gtk_container_set_border_width(GTK_CONTAINER(window), 10);
    gtk_window_set_default_size(GTK_WINDOW(window), 400, 300);
    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    // Create an image widget and load the image
    image = gtk_image_new_from_file(image_path);

    if (!image) {
        g_printerr("Error loading image: %s\n", image_path);
        gtk_widget_destroy(window);
        return;
    }

    // Add the image widget to the window
    gtk_container_add(GTK_CONTAINER(window), image);

    // Show all widgets
    gtk_widget_show_all(window);

    // Start the GTK main loop
    gtk_main();
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        g_printerr("Usage: %s HangmanDiagram/0\n", argv[0]);
        return 1;
    }

    // Call the display_image function with the provided image path
    display_image(argv[1]);

    return 0;
}

