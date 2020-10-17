#include <string.h>
#include <gtk/gtk.h>

#include "../hdr/segmentation.h"

gboolean on_Main_window_delete(GtkWidget * widget, gpointer data);
void on_Main_window_destroy(GtkWidget *widget, gpointer data);
void on_imageChooser_set_file(GtkFileChooserButton *button);
void on_imageAnalyse_clicked(GtkWidget *widget, gpointer data);

char *filename;

static GtkTextBuffer *buffer;
static GtkImage *image;

int setup()
{
    GtkBuilder *builder;
    GtkWidget *window;
    GtkWidget *textView;
    GtkWidget *imageWidget;
    GError *err = NULL;

    builder = gtk_builder_new();
    if (gtk_builder_add_from_file(builder, "UI/ocr.glade", &err) == 0)
    {
        fprintf(stderr, "Error adding build from file. Error: %s\n", err -> message);
        return 1;
    }

    window = GTK_WIDGET
            (
                    gtk_builder_get_object(builder, "Main_window")
            );

    textView = GTK_WIDGET
            (
                    gtk_builder_get_object(builder, "imageContent")
            );

    buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(textView));

    imageWidget = GTK_WIDGET
            (
                    gtk_builder_get_object(builder, "chosenImage")
            );

    image = GTK_IMAGE(imageWidget);

    gtk_builder_connect_signals(builder, NULL);

    g_object_unref(G_OBJECT(builder));

    gtk_widget_show(window);

    return 0;
}

gboolean on_Main_window_delete(
        __attribute__ ((unused)) GtkWidget *widget, __attribute__ ((unused)) gpointer data)
{
    g_print("Quitting app...\n");
    return TRUE;
}

void on_Main_window_destroy(
        __attribute__ ((unused)) GtkWidget *widget, __attribute__ ((unused)) gpointer data)
{
    gtk_main_quit();
    g_print("App closed\n");
}

void on_imageChooser_set_file(GtkFileChooserButton *button)
{
    filename = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(button));
    gtk_image_set_from_file(image, filename);
}

void on_imageAnalyse_clicked(
        __attribute__ ((unused)) GtkWidget *widget, __attribute__ ((unused)) gpointer data)
{
    g_print(filename);
    gtk_text_buffer_set_text(buffer, filename, -1);

    /*
     * IMAGE image = Load_image(filename);
     * if NULL
     * CHARACTERS characters = Segment_image(image.rows, image.columns, image.pixels);*/
}