#include <gtk/gtk.h>
#include "mainwindow.h"

void activate(GtkApplication *app, gpointer user_data) {
  GtkBuilder *builder;
  GtkWidget *window;
  GError *error = NULL;

  builder = gtk_builder_new();

  if (!gtk_builder_add_from_file(builder, "ui/interface.glade", &error)) {
    g_printerr("Error loading file: %s\n", error->message);
    g_clear_error(&error);
    return;
  }

  window = GTK_WIDGET(gtk_builder_get_object(builder, "main_window"));
  if (!window) {
    g_printerr("Error: Could not find 'main_window' in the UI file.\n");
    g_object_unref(builder);
    return;
  }

  gtk_window_set_application(GTK_WINDOW(window), app);
  gtk_widget_show_all(window);

  g_object_unref(builder);
}
