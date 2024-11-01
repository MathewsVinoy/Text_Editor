#include <gtk/gtk.h>
#include "mainwindow.h"

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

void on_text_buffer_changed(GtkTextBuffer *buffer, GtkTextBuffer *line_numbers_buffer);