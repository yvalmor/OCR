#ifndef OCR_UI_H
#define OCR_UI_H

#include <gtk/gtk.h>

/**
 * Loads the UI and display it on the screen
 *
 * @author Yvon Morice
 * @return 1 if there was an error else 0
 */
int setup();


/**
 * Sets the text as the result of the analysis
 *
 * @author Yvon Morice
 * @param text, char[]
 */
void set_text(char *text);


/**
 * A function called by gtk when the user quit the program,
 * tells gtk to destroy the main window
 *
 * @author Yvon Morice
 * @param widget, the main window (will be destroyed)
 * @param data, unused parameter, passed by gtk
 * @return TRUE to tell gtk the widget was destroyed
 */
gboolean on_Main_window_delete(GtkWidget * widget, gpointer data);


/**
 * A function called by gtk when the main window is destroyed,
 * tells gtk to stop
 *
 * @author Yvon Morice
 * @param widget, unused parameter, the main window (which has been destroyed)
 * @param data, unused parameter, passed by gtk
 */
void on_Main_window_destroy(GtkWidget *widget, gpointer data);


/**
 * A function called by gtk when the user has chosen an image to analyse,
 * changes the image viewed on the left of the UI
 *
 * @author Yvon Morice
 * @param button, the button widget which has been used to launch the file chooser
 */
void on_imageChooser_set_file(GtkFileChooserButton *button);


/**
 * A function called by gtk when the user has pushed the Analyse image button,
 * tells the program to load the image
 *
 * @author Yvon Morice
 * @param widget, unused parameter, passed by gtk, the widget button
 * @param data, unused parameter, passed by gtk
 */
void on_imageAnalyse_clicked(GtkWidget *widget, gpointer data);


/**
 * A function to launch the training of the neural network
 *
 * @author Yvon Morice
 * @param button, the button that launched the action
 * @param user_data, unused, data sent through the action
 */
void on_startTrainingButton_clicked(GtkButton *button,
                                    __attribute__ ((unused)) gpointer user_data);


/**
 * A function to trigger the automatic rotation of the image
 *
 * @author Yvon Morice
 * @param button, unused, the check button that triggered the call
 * @param user_data, unused, data sent through the action
 */
void on_autoRotationCheckButton_toggled(
        __attribute__ ((unused)) GtkToggleButton *button,
        __attribute__ ((unused)) gpointer user_data);


/**
* A function to trigger the save of the result of the analysis
 *
 * @author Yvon Morice
 * @param button, unused, the check button that triggered the call
 * @param user_data, unused, data sent through the action
 */
void on_saveButton_clicked(
        __attribute__ ((unused)) GtkButton *button,
        __attribute__ ((unused)) gpointer user_data);


/**
 * A function to set the text of the text view at the right of the UI
 *
 * @author Yvon Morice
 * @param text, char
 */
void set_text(char *text);

#endif //OCR_UI_H
