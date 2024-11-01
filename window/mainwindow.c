#include <gtk/gtk.h>
#include "mainwindow.h"

void activate (GtkApplication *app,gpointer  user_data)
{
  GtkWidget *window;

  window = gtk_application_window_new (app);
  gtk_window_set_title (GTK_WINDOW (window), "Hello");
  gtk_window_set_default_size (GTK_WINDOW (window), 600, 400);

  gtk_window_present (GTK_WINDOW (window));
}
