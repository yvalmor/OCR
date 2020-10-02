#include <stdio.h>
#include <gtk/gtk.h>

// Image
static GtkWidget *Image;
// Text view;
static GtkWidget *TextView;
// Windows
static GtkWidget *Main_window;

// Prototypes
void Analyse(GtkWidget *file_selection);
void Choose_image();
void Set_image(GtkWidget *file_selection);
void Set_text(const gchar *path);
int Check_file(const gchar *path, FILE *file);

int main(int argc, char **argv)
{
    // Separator
    GtkWidget *vSeparator;
    GtkWidget *hSeparator;

    // Containers
    GtkWidget *scroll_bar;
    GtkWidget *main_hBox;
    GtkWidget *image_vBox;
    GtkWidget *image_button_hBox;

    // Buttons
    GtkWidget *analyse_image;
    GtkWidget *choose_button;

    // GTK+ initialisation
    gtk_init(&argc, &argv);

    // Main window creation
    Main_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    g_signal_connect(G_OBJECT(Main_window),
            "delete-event", G_CALLBACK(gtk_main_quit), NULL);

    // Main window settings
    gtk_window_set_title(GTK_WINDOW(Main_window), "OCR");
    gtk_window_set_default_size(GTK_WINDOW(Main_window), 1280, 720);
    gtk_window_set_position(GTK_WINDOW(Main_window), GTK_WIN_POS_CENTER);

    // Event binding
    choose_button = gtk_button_new_with_label("Choose an image");
    g_signal_connect_swapped(G_OBJECT(choose_button),
                     "clicked", G_CALLBACK(Choose_image), NULL);

    analyse_image = gtk_button_new_with_label("Analyse");
    /*g_signal_connect_swapped(G_OBJECT(analyse_image),
                     "clicked", G_CALLBACK(Analyse), path);*/

    // Image initialisation
    Image = gtk_image_new();

    // Text view initialisation
    TextView = gtk_text_view_new();
    gtk_text_view_set_editable(GTK_TEXT_VIEW(TextView), FALSE);

    // Separator initialisation
    vSeparator = gtk_vseparator_new();
    hSeparator = gtk_hseparator_new();

    // Containers initialisation
    main_hBox = gtk_hbox_new(FALSE, 0);
    image_vBox = gtk_vbox_new(FALSE, 0);
    image_button_hBox = gtk_hbox_new(TRUE, 0);
    scroll_bar = gtk_scrolled_window_new(NULL, NULL);

    // Containers binding
    gtk_box_pack_start(GTK_BOX(main_hBox), image_vBox, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(main_hBox), vSeparator, FALSE, FALSE, 7);
    gtk_box_pack_start(GTK_BOX(main_hBox), scroll_bar, TRUE, TRUE, 0);

    gtk_box_pack_start(GTK_BOX(image_vBox), Image, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(image_vBox), hSeparator, FALSE, FALSE, 7);
    gtk_box_pack_start(GTK_BOX(image_vBox), image_button_hBox, FALSE, TRUE, 0);

    gtk_box_pack_start(GTK_BOX(image_button_hBox), choose_button, TRUE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(image_button_hBox), analyse_image, TRUE, FALSE, 0);

    gtk_container_add(GTK_CONTAINER(scroll_bar), TextView);
    gtk_container_add(GTK_CONTAINER(Main_window), main_hBox);

    // Showing main window
    gtk_widget_show_all(Main_window);

    // Main loop
    gtk_main();

    return EXIT_SUCCESS;
}

//TODO
void Analyse(GtkWidget *file_selection)
{
    // Variables
    const gchar *path;

    path = gtk_file_selection_get_filename(GTK_FILE_SELECTION(file_selection));

    /* pre-treatment
     * treatment
     * analysis
     * display */

    // Set_text("generated.txt");

    printf("%s", path);
}

void Choose_image()
{
    GtkWidget *file_selection;

    file_selection = gtk_file_selection_new(
            g_locale_to_utf8("Choose an image", -1, NULL, NULL, NULL));
    gtk_widget_show(file_selection);

    g_signal_connect(G_OBJECT(GTK_FILE_SELECTION(file_selection)->ok_button),
                     "clicked", G_CALLBACK(Set_image), file_selection);

    g_signal_connect_swapped(G_OBJECT(GTK_FILE_SELECTION(file_selection)->cancel_button),
                             "clicked", G_CALLBACK(gtk_widget_destroy), file_selection);
}

void Set_image(GtkWidget *file_selection)
{
    // Variables
    const gchar *path;

    // Getting the path of the image and setting it
    path = gtk_file_selection_get_filename(GTK_FILE_SELECTION(file_selection));
    gtk_image_set_from_file(GTK_IMAGE(Image), path);

    gtk_widget_destroy(file_selection);
}

void Set_text(const gchar *path)
{
    // Variables
    GtkTextBuffer *buffer;
    GtkTextIter start;
    GtkTextIter end;
    FILE *file;
    gchar read[1024];

    buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(TextView));

    // File opening
    file = fopen(path, "rt");

    // Check if file is NULL
    if (!Check_file(path, file))
        return;

    // File reading
    gtk_text_buffer_get_start_iter(buffer, &start);
    gtk_text_buffer_get_end_iter(buffer, &end);
    gtk_text_buffer_delete(buffer, &start, &end);

    while (fgets(read, 1024, file))
    {
        gtk_text_buffer_get_end_iter(buffer, &end);
        gtk_text_buffer_insert(
                buffer, &end,
                g_locale_to_utf8(read, -1, NULL, NULL, NULL), -1);
    }

    // File closing
    fclose(file);
}

int Check_file(const gchar *path, FILE *file)
{
    if (file == NULL)
    {
        GtkWidget *dialog;

        // Opening of a dialog to signal the user a problem
        dialog = gtk_message_dialog_new(
                GTK_WINDOW(Main_window),
                GTK_DIALOG_MODAL,
                GTK_MESSAGE_ERROR,
                GTK_BUTTONS_OK,
                "Impossible to open file:\n%s",
                g_locale_to_utf8(path, -1, NULL, NULL, NULL));

        gtk_dialog_run(GTK_DIALOG(dialog));
        gtk_widget_destroy(dialog);

        return 0;
    }

    return 1;
}