#include <stdlib.h>
#include <gtk/gtk.h>

// Prototypes
void analyse();
void choose_image();

// Image
GtkWidget *Image;
// Text view;
GtkWidget *TextView;
// File chooser
GtkWidget *FileChooser;

int main(int argc, char **argv)
{
    // Windows
    GtkWidget *MainWindow;
    // Separator
    GtkWidget *VSeparator;
    // Containers
    GtkWidget *ScrollText;
    GtkWidget *MainHBox;
    GtkWidget *ImageVBox;
    GtkWidget *ImageButtonHBox;
    // Buttons
    GtkWidget *AnalyseImage;
    GtkWidget *ChooseImage;

    // GTK+ initialisation
    gtk_init(&argc, &argv);

    // Main window creation
    MainWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    g_signal_connect(G_OBJECT(MainWindow), "delete-event", G_CALLBACK(gtk_main_quit), NULL);

    // Main window settings
    gtk_window_set_title(GTK_WINDOW(MainWindow), "OCR");
    gtk_window_set_default_size(GTK_WINDOW(MainWindow), 1280, 720);
    gtk_window_set_position(GTK_WINDOW(MainWindow), GTK_WIN_POS_CENTER);

    // Event binding
    ChooseImage = gtk_button_new_with_label("Choose image");
    g_signal_connect(G_OBJECT(ChooseImage), "clicked", G_CALLBACK(choose_image), FileChooser);

    AnalyseImage = gtk_button_new_with_label("Analyse");
    g_signal_connect(G_OBJECT(AnalyseImage), "clicked", G_CALLBACK(analyse), "path");

    // Image initialisation
    Image = gtk_image_new();

    // Text view initialisation
    TextView = gtk_text_view_new();

    // Separator initialisation
    VSeparator = gtk_vseparator_new();

    // Containers binding
    MainHBox = gtk_hbox_new(FALSE, 0);
    ImageVBox = gtk_vbox_new(FALSE, 0);
    ImageButtonHBox = gtk_hbox_new(TRUE, 0);
    ScrollText = gtk_scrolled_window_new(NULL, NULL);

    gtk_box_pack_start(GTK_BOX(MainHBox), ImageVBox, TRUE, TRUE, 0);

    gtk_box_pack_start(GTK_BOX(ImageVBox), Image, TRUE, TRUE, 0);
    gtk_box_pack_start(GTK_BOX(ImageVBox), ImageButtonHBox, FALSE, TRUE, 0);

    gtk_box_pack_start(GTK_BOX(ImageButtonHBox), ChooseImage, TRUE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(ImageButtonHBox), AnalyseImage, TRUE, FALSE, 0);

    gtk_box_pack_start(GTK_BOX(MainHBox), VSeparator, FALSE, FALSE, 0);

    gtk_box_pack_start(GTK_BOX(MainHBox), ScrollText, TRUE, TRUE, 0);

    gtk_container_add(GTK_CONTAINER(ScrollText), TextView);

    gtk_container_add(GTK_CONTAINER(MainWindow), MainHBox);

    // Main loop + showing main window
    gtk_widget_show_all(MainWindow);
    gtk_main();

    return EXIT_SUCCESS;
}

//TODO
void analyse()
{
    /* pre-treatment
     * treatment
     * analysis
     * display */
}

//TODO
void choose_image()
{
    /* choice of image
     * loading */
    //Image = gtk_image_set_from_file("path")
}
