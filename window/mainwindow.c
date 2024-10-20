#include <gtk/gtk.h>
#include "mainwindow.h"

void on_text_buffer_changed(GtkTextBuffer *buffer, GtkTextBuffer *line_numbers_buffer);

void activate(GtkApplication *app, gpointer user_data) {
  GtkBuilder *builder;
  GtkWidget *window;
  GtkTextView *line_number, *main_area;
  GtkTextBuffer *buffer_line , *buffer_main;
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

  main_area = GTK_TEXT_VIEW(gtk_builder_get_object(builder,"textview1"));
  line_number = GTK_TEXT_VIEW(gtk_builder_get_object(builder, "textview_line_numbers"));

  buffer_main = gtk_text_view_get_buffer(main_area);
  buffer_line = gtk_text_view_get_buffer(line_number);

  g_signal_connect(buffer_main, "changed", G_CALLBACK(on_text_buffer_changed), buffer_line);

  gtk_text_buffer_set_text(buffer_line, "1", -1);

  gtk_window_set_application(GTK_WINDOW(window), app);
  gtk_widget_show_all(window);

  g_object_unref(builder);
}

void update_line_numbers(GtkTextBuffer *buffer, GtkTextBuffer *line_numbers_buffer) {
    GtkTextIter start, end;
    gint line_count;
    gchar *line_numbers;

    gtk_text_buffer_get_start_iter(buffer, &start);
    gtk_text_buffer_get_end_iter(buffer, &end);

    line_count = gtk_text_buffer_get_line_count(buffer);

    line_numbers = g_strdup_printf("1\n");
    for (gint i = 2; i <= line_count; i++) {
        gchar *temp = g_strdup_printf("%s%d\n", line_numbers, i);
        g_free(line_numbers);
        line_numbers = temp;
    }

    gtk_text_buffer_set_text(line_numbers_buffer, line_numbers, -1);

    g_free(line_numbers);
}

void on_text_buffer_changed(GtkTextBuffer *buffer, GtkTextBuffer *line_numbers_buffer) {
    update_line_numbers(buffer, line_numbers_buffer);
}
