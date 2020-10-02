#include <stdlib.h>
#include <gtk/gtk.h>

void analyse(char path[]);
void choose_image(GtkWidget *fileChooser);

int main(int argc, char **argv)
{
    // Variables
    GtkWidget *MainWindow = NULL;
    GtkWidget *FileChooser = NULL;
    GtkWidget *ChooseImage = NULL;

    // GTK+ initialisation
    gtk_init(&argc, &argv);

    // Main window creation
    MainWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    g_signal_connect(G_OBJECT(MainWindow), "delete-event", G_CALLBACK(gtk_main_quit), NULL);

    // Main window settings
    gtk_window_set_title(GTK_WINDOW(MainWindow), "OCR");
    gtk_window_set_default_size(GTK_WINDOW(MainWindow), 1280, 720);
    gtk_window_set_position(GTK_WINDOW(MainWindow), GTK_WIN_POS_CENTER);

    ChooseImage = gtk_button_new_with_label("Choose image");
    g_signal_connect(G_OBJECT(ChooseImage), "clicked", G_CALLBACK(choose_image), FileChooser);
    gtk_container_add(GTK_CONTAINER(MainWindow), ChooseImage);

    // Main loop + showing main window
    gtk_widget_show_all(MainWindow);
    gtk_main();

    return EXIT_SUCCESS;
}

//TODO
void analyse(char path[])
{
    /* pre-treatment
     * treatment
     * analysis
     * display */
}

//TODO
void choose_image(GtkWidget *fileChooser)
{
    /* choice of image
     * loading */
}
