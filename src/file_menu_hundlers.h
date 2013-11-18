#ifndef FILE_MENU_H
#define FILE_MENU_H
#include <gdk/gdk.h>
#include <gtk/gtk.h>
#include <glade/glade.h>
/* #################### This is the "File" menu item functions (New, Saving, Saving as, quit options) #################################*/

gchar *file_saving;

int on_save_button_clicked(GtkFileChooserDialog *window,GtkButton *save_button);
int on_save_as_button_clicked(GtkFileChooserDialog *window,GtkButton *save_button);
void saving();
void on_cancel_button_clicked(GtkWindow *window,GtkButton *cancel_button);
void on_new_activate(GtkTextView *c_program ,GtkMenuItem *new_item);
void on_save_as_activate(GtkTextView *c_program ,GtkMenuItem *new_item);
void on_save_activate(GtkTextView *c_program ,GtkMenuItem *new_item);


#endif
