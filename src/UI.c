#include <string.h>

#include "../hdr/UI.h"
#include "../hdr/bitmap.h"
#include "../hdr/text.h"

char *filename;

static GtkTextBuffer *buffer;
static GtkImage *image;
static GtkScale *angleScale;
static GtkWidget *window;

GtkFileChooser *trainingFileChooser, *solutionFileChooser;
GtkWidget *startButton;
GtkWidget *trainingStartButton;
GtkProgressBar *trainingProgress;

static int autoRot;

int setup()
{
    GtkBuilder *builder;
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
            gtk_builder_get_object(builder, "imageAnalyse"));

    trainingStartButton = GTK_WIDGET(
            gtk_builder_get_object(builder, "startTrainingButton"));

    trainingProgress = GTK_PROGRESS_BAR(
            gtk_builder_get_object(builder, "trainingProgressBar"));

    angleScale = GTK_SCALE(
            gtk_builder_get_object(builder, "angleScale"));

    gtk_range_set_range(GTK_RANGE(angleScale), 0, 360);
    gtk_range_set_value(GTK_RANGE(angleScale), 0);

    gtk_builder_connect_signals(builder, NULL);

    g_object_unref(G_OBJECT(builder));

    gtk_widget_show(window);

    return 0;
}


gboolean on_Main_window_delete(
        GtkWidget *widget, __attribute__ ((unused)) gpointer data)
{
    g_print("Quitting app...\n");
    gtk_widget_destroy(widget);
    return TRUE;
}


void on_Main_window_destroy(
        __attribute__ ((unused)) GtkWidget *widget,
        __attribute__ ((unused)) gpointer data)
{
    gtk_main_quit();
    g_print("App closed\n");
}


void on_imageChooser_file_set(GtkFileChooserButton *button)
{
    filename = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(button));

    GdkPixbuf *pixBuf =
        gdk_pixbuf_new_from_file_at_scale(filename,
                                          600,
                                          600,
                                          TRUE,
                                          NULL);

    gtk_image_set_from_pixbuf(image, pixBuf);
}


void on_imageAnalyse_clicked(GtkWidget *widget,
        __attribute__ ((unused)) gpointer data)
{
    if (filename == NULL)
        return;

    gtk_widget_set_sensitive(widget, FALSE);
    gtk_widget_set_sensitive(trainingStartButton, FALSE);

    int rotationAngle = gtk_range_get_value(GTK_RANGE(angleScale));
    loadImage(filename, autoRot, rotationAngle);

    gtk_widget_set_sensitive(widget, TRUE);
    gtk_widget_set_sensitive(trainingStartButton, TRUE);
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
    gtk_widget_set_sensitive(startButton, FALSE);

    GSList *trainingList = gtk_file_chooser_get_filenames(
                        GTK_FILE_CHOOSER(trainingFileChooser));
    GSList *solutionList = gtk_file_chooser_get_filenames(
                        GTK_FILE_CHOOSER(solutionFileChooser));

    if (trainingList == NULL || solutionList == NULL)
    {
        gtk_widget_set_sensitive(GTK_WIDGET(button), TRUE);
        gtk_widget_set_sensitive(startButton, TRUE);
        return;
    }

    guint nbTrainingFiles = g_slist_length(trainingList);
    guint nbSolutionFiles = g_slist_length(solutionList);

    if (nbTrainingFiles != nbSolutionFiles)
    {
        g_slist_free(trainingList);
        g_slist_free(solutionList);

        gtk_widget_set_sensitive(GTK_WIDGET(button), TRUE);
        gtk_widget_set_sensitive(startButton, TRUE);
        return;
    }

    int rotationAngle = gtk_range_get_value(GTK_RANGE(angleScale));

    guint index = 0;
    gdouble value = 0.0;

    gtk_progress_bar_set_fraction(trainingProgress, value);

    int limit = 100;
    for (int i = 0; i < limit; i++)
    {
        while (trainingList != NULL)
        {
            char *trainingFile = trainingList->data;
            char *solutionFile = solutionList->data;

            FILE *fp = fopen(solutionFile, "r");
            if (fp)
            {
                loadImage_with_training(trainingFile, autoRot, rotationAngle, fp);
                fclose(fp);
            }

            index++;

            value = index / nbTrainingFiles;
            gtk_progress_bar_set_fraction(trainingProgress, value);

            trainingList = trainingList->next;
            solutionList = solutionList->next;
        }
        trainingList = gtk_file_chooser_get_filenames(
                            GTK_FILE_CHOOSER(trainingFileChooser));
        solutionList = gtk_file_chooser_get_filenames(
                            GTK_FILE_CHOOSER(solutionFileChooser));
    }

    g_slist_free(trainingList);
    g_slist_free(solutionList);

    gtk_widget_set_sensitive(GTK_WIDGET(button), TRUE);
    gtk_widget_set_sensitive(startButton, TRUE);
}

void on_autoRotationCheckButton_toggled(
            __attribute__ ((unused)) GtkToggleButton *button,
            __attribute__ ((unused)) gpointer user_data)
{
    autoRot = !autoRot;

    gtk_widget_set_sensitive(
            GTK_WIDGET(angleScale),
            autoRot ? FALSE : TRUE);
}

void on_saveButton_clicked(
            __attribute__ ((unused)) GtkButton *button,
            __attribute__ ((unused)) gpointer user_data)
{
    gchar *text;
    GtkTextIter start, end;

    gtk_text_buffer_get_bounds(buffer, &start, &end);
    text = gtk_text_buffer_get_text(buffer, &start, &end, FALSE);

    if (strlen(text) == 0)
    {
        g_free(text);
        return;
    }

    GtkWidget *dialog;
    GtkFileChooser *chooser;
    GtkFileChooserAction action = GTK_FILE_CHOOSER_ACTION_SAVE;
    gint res;

    dialog = gtk_file_chooser_dialog_new("Save file",
                                         GTK_WINDOW(window),
                                         action,
                                         "Cancel",
                                         GTK_RESPONSE_CANCEL,
                                         "Save",
                                         GTK_RESPONSE_ACCEPT,
                                         NULL);

    chooser = GTK_FILE_CHOOSER(dialog);

    gtk_file_chooser_set_do_overwrite_confirmation(chooser, TRUE);

    gtk_file_chooser_set_current_name(chooser, "OCR result.txt");

    gtk_window_set_default_size(GTK_WINDOW(dialog), 400, 400);
    gtk_window_set_resizable(GTK_WINDOW(dialog), TRUE);

    res = gtk_dialog_run(GTK_DIALOG(dialog));

    if (res == GTK_RESPONSE_ACCEPT)
    {
        char *filename;
        filename = gtk_file_chooser_get_filename(chooser);
        save_Text(filename, text);
        g_free(filename);
    }

    g_free(text);
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
