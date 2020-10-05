#include <gtk/gtk.h>

#include "../hdr/UI.h"

// Prototypes
static void Container_setup(GtkWidget *Notebook, GtkWidget *Label)

static void Choose_images(void);
static void Choose_solution(void);

static void Launch_training(void);

// Filenames
const gchar *image_dir;
const gchar *solution;

void Training_setup(GtkWidget *Notebook, GtkWidget *Label)
{


}

static void Container_setup(GtkWidget *Notebook, GtkWidget *Label)
{
    GtkWidget *main_hbox;

    gtk_notebook_append_page(GTK_NOTEBOOK(Notebook), main_hBox, Label);
}

static void Choose_images(void)
{
    
}