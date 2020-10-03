#include <gtk/gtk.h>

#include "../hdr/UI.h"

// Prototypes
static void Window_setup(void);
static void Image_setup(void);
static void TextView_setup(void);

static void Check_size(GtkWidget *image);

static void Separator_setup(void);
static void Button_setup(void);
static void Container_setup(void);

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
// Separators
static GtkWidget *vSeparator;
static GtkWidget *hSeparator;
// Buttons
static GtkWidget *choose_button;
static GtkWidget *analyse_image;
// Path
static const gchar *path;

void Setup(void)
{
    Window_setup();
    Image_setup();
    TextView_setup();

    Separator_setup();
    Button_setup();

    Container_setup();

    gtk_widget_show_all(Main_window);
}

static void Window_setup(void)
{
    // Main window settings
    gtk_window_set_title(GTK_WINDOW(Main_window), "OCR");

    // Main window creation
    Main_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

    //Main window settings
    g_signal_connect(G_OBJECT(Main_window),
                     "delete-event", G_CALLBACK(gtk_main_quit), NULL);
    gtk_window_set_position(GTK_WINDOW(Main_window), GTK_WIN_POS_CENTER);
    gtk_window_set_default_size(GTK_WINDOW(Main_window), 1280, 720);
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

static void Check_size(GtkWidget *image)
{
    // If the size of the image is too big we resize it
    if (image->allocation.height > 600 || image->allocation.width > 600)
        gtk_widget_set_size_request(image, 600, 600);
}

static void Separator_setup()
{
    // Separator initialisation
    vSeparator = gtk_vseparator_new();
    hSeparator = gtk_hseparator_new();
}

static void Button_setup()
{
    // Event binding
    choose_button = gtk_button_new_with_label("Choose an image");
    g_signal_connect_swapped(G_OBJECT(choose_button),
                             "clicked", G_CALLBACK(Choose_image), NULL);

    analyse_image = gtk_button_new_with_label("Analyse");
    g_signal_connect_swapped(G_OBJECT(analyse_image),
                     "clicked", G_CALLBACK(Analyse), NULL);
}

static void Container_setup()
{
    GtkWidget *scroll_bar;
    GtkWidget *image_scroll;
    GtkWidget *main_hBox;
    GtkWidget *image_vBox;
    GtkWidget *image_button_hBox;

    // Containers initialisation
    main_hBox = gtk_hbox_new(FALSE, 0);
    image_vBox = gtk_vbox_new(FALSE, 0);
    image_button_hBox = gtk_hbox_new(TRUE, 0);
    scroll_bar = gtk_scrolled_window_new(NULL, NULL);
    image_scroll = gtk_scrolled_window_new(NULL, NULL);

    gtk_scrolled_window_set_policy
        (
            GTK_SCROLLED_WINDOW(image_scroll), GTK_POLICY_AUTOMATIC,
            GTK_POLICY_AUTOMATIC
        );

    g_signal_connect_swapped(G_OBJECT(image_scroll),
                             "size-allocate", G_CALLBACK(Check_size), image_scroll);

    // Containers binding
    gtk_box_pack_start(GTK_BOX(main_hBox), image_vBox, TRUE, TRUE, 7);
    gtk_box_pack_start(GTK_BOX(main_hBox), vSeparator, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(main_hBox), scroll_bar, TRUE, TRUE, 7);

    gtk_box_pack_start(GTK_BOX(image_vBox), image_scroll, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(image_vBox), hSeparator, FALSE, FALSE, 7);
    gtk_box_pack_start(GTK_BOX(image_vBox), image_button_hBox, FALSE, TRUE, 0);

    gtk_box_pack_start(
            GTK_BOX(image_button_hBox), choose_button, TRUE, FALSE, 0);
    gtk_box_pack_start(
            GTK_BOX(image_button_hBox), analyse_image, TRUE, FALSE, 0);

    gtk_scrolled_window_add_with_viewport(
            GTK_SCROLLED_WINDOW(image_scroll), Image);

    gtk_container_add(GTK_CONTAINER(scroll_bar), TextView);
    gtk_container_add(GTK_CONTAINER(Main_window), main_hBox);
}

//TODO
static void Analyse(GtkWidget *file_selection)
{
    /* pre-treatment
     * treatment
     * analysis
     * display */

    // Set_text("generated.txt");

    printf("%s", path);
    Set_text("");
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
            "Open File", GTK_WINDOW(Main_window), action,
            "Cancel", GTK_RESPONSE_CANCEL,
            "Open", GTK_RESPONSE_ACCEPT,
            NULL);

    gtk_file_chooser_add_filter(GTK_FILE_CHOOSER(file_chooser), filter);

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

    gtk_image_clear(GTK_IMAGE(Image));
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