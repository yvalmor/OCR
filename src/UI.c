#include <gtk/gtk.h>

void on_Main_window_destroy();

void setup()
{
    GtkBuilder *builder;
    GtkWidget *window;

    builder = gtk_builder_new();
    gtk_builder_add_from_file(builder, "ocr.glade", NULL);

    window = GTK_WIDGET(
            gtk_builder_get_object(builder, "Main_window")
            );
    gtk_builder_connect_signals(builder, NULL);

    g_object_unref(builder);

    gtk_widget_show(GTK_WIDGET(window));
}

void on_Main_window_destroy()
{
    gtk_main_quit();
}