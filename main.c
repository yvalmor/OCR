#include <stdlib.h>
#include <gtk/gtk.h>

int main(int argc, char **argv)
{
    // Variables
    GtkWidget * MainWindow = NULL;
    const gchar *title = "OCR";
    const gint *width = 1280;
    const gint *height = 720;

    // GTK+ initialisation
    gtk_init(&argc, &argv);

    // Main window creation
    MainWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    g_signal_connect(G_OBJECT(MainWindow), "delete-event", G_CALLBACK(gtk_main_quit), NULL);
    void gtk_window_set_title(MainWindow, title);
    void gtk_window_set_default_size(MainWindow, width, height);
    void gtk_window_set_position(MainWindow, GTK_WIN_POS_CENTER);

    // Main loop + showing main window
    gtk_widget_show(MainWindow);
    gtk_main();

    return EXIT_SUCCESS;
}