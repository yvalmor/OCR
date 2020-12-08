#include <string.h>
#include <gtk/gtk.h>

#include "../hdr/bitmap.h"

gboolean on_Main_window_delete(GtkWidget * widget, gpointer data);
void on_Main_window_destroy(GtkWidget *widget, gpointer data);
void on_imageChooser_set_file(GtkFileChooserButton *button);
void on_imageAnalyse_clicked(GtkWidget *widget, gpointer data);

char *filename;

static GtkTextBuffer *buffer;
static GtkImage *image;
GtkFileChooser *trainingFileChooser, *solutionFileChooser;
GtkWidget *startButton;
GtkProgressBar *trainingProgress;

/**
 * Loads the UI and display it on the screen
 *
 * @author Yvon Morice
 * @return 1 if there was an error else 0
 */
int setup()
{
    GtkBuilder *builder;
    GtkWidget *window;
    GtkWidget *textView;
    GtkWidget *imageWidget;
    GError *err = NULL;

    builder = gtk_builder_new();
    if (gtk_builder_add_from_file(builder, "../UI/ocr.glade", &err) == 0)
    {
        fprintf(stderr,
                "Error adding build from file. Error: %s\n", err -> message);
        return 1;
    }

    window = GTK_WIDGET(
            gtk_builder_get_object(builder, "Main_window"));

    textView = GTK_WIDGET(
            gtk_builder_get_object(builder, "imageContent"));

    buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(textView));

    imageWidget = GTK_WIDGET(
            gtk_builder_get_object(builder, "chosenImage"));

    image = GTK_IMAGE(imageWidget);

    trainingFileChooser = GTK_FILE_CHOOSER(
            gtk_builder_get_object(builder, "trainingFileChooser"));
    solutionFileChooser = GTK_FILE_CHOOSER(
            gtk_builder_get_object(builder, "solutionFileChooser"));

    startButton = GTK_WIDGET(
            gtk_builder_get_object(builder, "startTrainingButton"));

    trainingProgress = GTK_PROGRESS_BAR(
            gtk_builder_get_object(builder, "trainingProgressBar"));

    gtk_builder_connect_signals(builder, NULL);

    g_object_unref(G_OBJECT(builder));

    gtk_widget_show(window);

    return 0;
}

/**
 * A function called by gtk when the user quit the program,
 * tells gtk to destroy the main window
 *
 * @author Yvon Morice
 * @param widget, the main window (will be destroyed)
 * @param data, unused parameter, passed by gtk
 * @return TRUE to tell gtk the widget was destroyed
 */
gboolean on_Main_window_delete(
        GtkWidget *widget, __attribute__ ((unused)) gpointer data)
{
    g_print("Quitting app...\n");
    gtk_widget_destroy(widget);
    return TRUE;
}

/**
 * A function called by gtk when the main window is destroyed,
 * tells gtk to stop
 *
 * @author Yvon Morice
 * @param widget, unused parameter, the main window (which has been destroyed)
 * @param data, unused parameter, passed by gtk
 */
void on_Main_window_destroy(
        __attribute__ ((unused)) GtkWidget *widget,
        __attribute__ ((unused)) gpointer data)
{
    gtk_main_quit();
    g_print("App closed\n");
}

/**
 * A function called by gtk when the user has chosen an image to analyse,
 * changes the image viewed on the left of the UI
 *
 * @author Yvon Morice
 * @param button, the button widget which has been used to launch the file chooser
 */
void on_imageChooser_file_set(GtkFileChooserButton *button)
{
    filename = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(button));
    gtk_image_set_from_file(image, filename);
}

/**
 * A function called by gtk when the user has pushed the Analyse image button,
 * tells the program to load the image
 *
 * @author Yvon Morice
 * @param widget, unused parameter, passed by gtk, the widget button
 * @param data, unused parameter, passed by gtk
 */
void on_imageAnalyse_clicked(
        __attribute__ ((unused)) GtkWidget *widget,
        __attribute__ ((unused)) gpointer data)
{
    if (filename == NULL)
        return;

    loadImage(filename);
}

/**
 * A function to launch the training of the neural network
 *
 * @author Yvon Morice
 * @param button, the button that launched the action
 * @param user_data, unused, data sent through the action
 */
void on_startTrainingButton_clicked(GtkButton *button,
                                    __attribute__ ((unused)) gpointer user_data)
{
    gtk_widget_set_sensitive(GTK_WIDGET(button), FALSE);
    //gtk_widget_set_sensitive(GTK_WIDGET(), FALSE);

    //GSList *
    //size_t nbFiles = 0;
}

/**
 * A function to set the text of the text view at the right of the UI
 *
 * @author Yvon Morice
 * @param text, the text to print
 */
void set_text(char *text)
{
    gtk_text_buffer_set_text(buffer, text, -1);
}
