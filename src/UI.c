#include <gtk/gtk.h>

void setup()
{
    GtkBuilder *builder;
    GtkWidget *window;
    GError *err = NULL;

    builder = gtk_builder_new();
    if (gtk_builder_add_from_file(builder, "UI/ocr.glade", &err) == 0)
    {
        fprintf(stderr, "Error adding build from file. Error: %s\n", err -> message);
        return;
    }

    window = GTK_WIDGET(
            gtk_builder_get_object(builder, "Main_window")
            );
    gtk_builder_connect_signals(builder, NULL);

    g_object_unref(builder);

    gtk_widget_show_all(window);
}

void on_Main_window_destroy()
{
    gtk_main_quit();
}

void on_choose_clicked()
{
    return;
}
