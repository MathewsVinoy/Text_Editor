#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <gtk/gtk.h>

void activate(GtkApplication *app, gpointer user_data);
void update_line_numbers(GtkTextBuffer *buffer, GtkTextBuffer *line_numbers_buffer);
void on_text_buffer_changed(GtkTextBuffer *buffer, GtkTextBuffer *line_numbers_buffer);

#endif 
