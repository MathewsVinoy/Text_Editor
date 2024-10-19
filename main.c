#include <gtk/gtk.h>

static void activate(GtkApplication *app, gpointer user_data) {
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

int main(int argc, char **argv) {
  GtkApplication *app;
  int status;

  app = gtk_application_new("com.example.GtkApp", G_APPLICATION_DEFAULT_FLAGS);

  g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);

  status = g_application_run(G_APPLICATION(app), argc, argv);

  g_object_unref(app);

  return status;
}
