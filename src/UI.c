#include <gtk/gtk.h>

#include "../hdr/UI.h"

// Prototypes
static void Window_setup(void);
static void Image_setup(void);
static void TextView_setup(void);

static void Separator_setup(GtkWidget *vSep, GtkWidget *hSep);
static void Button_setup(GtkWidget *choose_button, GtkWidget *analyse_image);
static void Container_setup(GtkWidget *vSep, GtkWidget *hSep,
                     GtkWidget *btn, GtkWidget *img_btn);

static void Analyse(GtkWidget *file_selection);
static void Choose_image();
static void Set_image(GtkWidget *file_selection);
static void Set_text(const gchar *path);
static int Check_file(const gchar *path, FILE *file);

// Image
static GtkWidget *Image;
// Text view;
static GtkWidget *TextView;
// Windows
static GtkWidget *Main_window;
// Path
static const gchar *path;

void Setup(void)
{
    // Variables
    GtkWidget *vSeparator;
    GtkWidget *hSeparator;

    GtkWidget *choose_button;
    GtkWidget *analyse_image;

    Window_setup();
    Image_setup();
    TextView_setup();

    Separator_setup(vSeparator, hSeparator);
    Button_setup(choose_button, analyse_image);

    Container_setup(vSeparator, hSeparator, choose_button, analyse_image);

    gtk_widget_show_all(Main_window);
}

static void Window_setup(void)
{
    // Main window creation
    Main_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    g_signal_connect(G_OBJECT(window_obj), "delete-event", G_CALLBACK(gtk_main_quit), NULL);

    // Main window settings
    gtk_window_set_title(GTK_WINDOW(Main_window), "OCR");
    gtk_window_set_default_size(GTK_WINDOW(Main_window), 1280, 720);
    gtk_window_set_position(GTK_WINDOW(Main_window), GTK_WIN_POS_CENTER);
}

static void Image_setup(void)
{
    // Image initialisation
    Image = gtk_image_new();
}

static void TextView_setup(void)
{
    // Text view initialisation
    TextView = gtk_text_view_new();
    gtk_text_view_set_editable(GTK_TEXT_VIEW(TextView), FALSE);
}

static void Separator_setup(GtkWidget *vSep, GtkWidget *hSep)
{
    // Separator initialisation
    vSeparator = gtk_vseparator_new();
    hSeparator = gtk_hseparator_new();
}

static void Button_setup(GtkWidget *choose_button, GtkWidget *analyse_image)
{
    // Event binding
    choose_button = gtk_button_new_with_label("Choose an image");
    g_signal_connect_swapped(G_OBJECT(choose_button),
                             "clicked", G_CALLBACK(Choose_image), NULL);

    analyse_image = gtk_button_new_with_label("Analyse");
    g_signal_connect_swapped(G_OBJECT(analyse_image),
                     "clicked", G_CALLBACK(Analyse), NULL);
}

static void Container_setup(GtkWidget *vSep, GtkWidget *hSep,
                     GtkWidget *btn, GtkWidget *img_btn)
{
    GtkWidget *scroll_bar;
    GtkWidget *main_hBox;
    GtkWidget *image_vBox;
    GtkWidget *image_button_hBox;

    // Containers initialisation
    main_hBox = gtk_hbox_new(FALSE, 0);
    image_vBox = gtk_vbox_new(FALSE, 0);
    image_button_hBox = gtk_hbox_new(TRUE, 0);
    scroll_bar = gtk_scrolled_window_new(NULL, NULL);

    // Containers binding
    gtk_box_pack_start(GTK_BOX(hBox), image_vBox, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(hBox), vSep, FALSE, FALSE, 7);
    gtk_box_pack_start(GTK_BOX(hBox), scroll_bar, TRUE, TRUE, 0);

    gtk_box_pack_start(GTK_BOX(vBox), Image, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(vBox), hSep, FALSE, FALSE, 7);
    gtk_box_pack_start(GTK_BOX(vBox), image_button_hBox, FALSE, TRUE, 0);

    gtk_box_pack_start(GTK_BOX(button_hBox), btn, TRUE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(button_hBox), img_btn, TRUE, FALSE, 0);

    gtk_container_add(GTK_CONTAINER(scroll_container), TextView);
    gtk_container_add(GTK_CONTAINER(window), main_hBox);
}

//TODO
static void Analyse(GtkWidget *file_selection)
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

static void Choose_image()
{
    GtkWidget *file_chooser;
    GtkFileChooserAction action;
    GtkFileFilter *filter;
    gint res;

    action = GTK_FILE_CHOOSER_ACTION_OPEN;
    filter = gtk_file_filter_new();
    gtk_file_filter_add_pixbuf_formats(filter);

    file_chooser = gtk_file_chooser_dialog_new (
            "Open File",
            window,
            action,
            _("_Cancel"),
            GTK_RESPONSE_CANCEL,
            _("_Open"),
            GTK_RESPONSE_ACCEPT,
            NULL);

    gtk_file_chooser_dialog_add_filter(GTK_FILE_CHOOSER(file_chooser), filter);

    res = gtk_dialog_run(GTK_DIALOG(file_chooser));
    if (res == GTK_RESPONSE_ACCEPT)
        Set_image(file_chooser);
    else
        gtk_widget_destroy(file_chooser);
}

static void Set_image(GtkWidget *file_chooser)
{
    // Getting the path of the image and setting it
    path = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(file_chooser));
    gtk_image_set_from_file(GTK_IMAGE(Image), path);

    gtk_widget_destroy(file_chooser);
}

static void Set_text(const gchar *path)
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

static int Check_file(const gchar *path, FILE *file)
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