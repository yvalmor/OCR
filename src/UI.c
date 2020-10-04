#include <gtk/gtk.h>

#include "../hdr/UI.h"

// Prototypes
static void Window_setup(void);
static void Notebook_setup(void);
static void Tab_setup(void);

// Main_window
GtkWidget *Main_window;

// Notebook
static GtkWidget *Notebook;
// Tabs
static GtkWidget *Analyse_tab;
static GtkWidget *Training_tab;

void Setup(void)
{
    Window_setup();

    Notebook_setup();
    Tab_setup();

    Analyse_setup(Notebook, Analyse_tab);
    Analyse_setup(Notebook, Training_tab);

    gtk_widget_show_all(Main_window);
}

static void Window_setup(void)
{
    // Main window creation
    Main_window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

    // Main window settings
    gtk_window_set_title(GTK_WINDOW(Main_window), "OCR");

    //Main window settings
    g_signal_connect(G_OBJECT(Main_window),
                     "delete-event", G_CALLBACK(gtk_main_quit), NULL);
    gtk_window_set_position(GTK_WINDOW(Main_window), GTK_WIN_POS_CENTER);
    gtk_window_set_default_size(GTK_WINDOW(Main_window), 1280, 720);
}

static void Notebook_setup(void)
{
    Notebook = gtk_notebook_new();

    gtk_container_add(GTK_CONTAINER(Main_window), Notebook);
}

static void Tab_setup(void)
{
    gchar *Analyse_label;
    gchar *Training_label;

    Analyse_label = g_strdup_printf("Analyse");
    Training_label = g_strdup_printf("Training");

    Analyse_tab = gtk_label_new(Analyse_label);
    Training_tab = gtk_label_new(Training_label);
}