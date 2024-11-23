#include <gtk/gtk.h>

GtkWidget *text_view;
GtkWidget *line_number_area;
GtkTextBuffer *buffer;
GtkAdjustment *vadj;

static void draw_line_numbers(GtkWidget *widget, cairo_t *cr, gpointer user_data) {
    GtkTextIter start_iter, end_iter;
    gint line_number = 1;
    gint y_offset = 0;
    gchar *line_text;
    PangoLayout *layout;
    PangoFontDescription *font_desc;
    gint line_height;

    cairo_set_source_rgb(cr, 0.5, 0.5, 0.5);

    gtk_text_buffer_get_bounds(buffer, &start_iter, &end_iter);

    layout = gtk_widget_create_pango_layout(widget, NULL);
    font_desc = pango_font_description_from_string("Monospace 10");
    pango_layout_set_font_description(layout, font_desc);
    pango_font_description_free(font_desc);

    PangoRectangle ink_rect, logical_rect;
    pango_layout_get_pixel_extents(layout, &ink_rect, &logical_rect);
    line_height = logical_rect.height;

    while (!gtk_text_iter_is_end(&start_iter)) {
        
        cairo_move_to(cr, 5, y_offset);
        
        line_text = g_strdup_printf("%d", line_number);
        pango_layout_set_text(layout, line_text, -1);
        pango_cairo_show_layout(cr, layout);
        g_free(line_text);

        y_offset += line_height;
        line_number++;

        gtk_text_iter_forward_line(&start_iter);
    }

    g_object_unref(layout);
}

static void on_text_change(GtkTextBuffer *buffer, gpointer user_data) {
    gtk_widget_queue_draw(GTK_WIDGET(user_data));
}

static void on_vadj_changed(GtkAdjustment *adj, gpointer user_data) {
    gtk_widget_queue_draw(GTK_WIDGET(user_data));
}

static void on_new_activate(GtkMenuItem *menu_item, gpointer user_data) {
    gtk_text_buffer_set_text(buffer, "", -1);
}

static void on_open_activate(GtkMenuItem *menu_item, gpointer user_data) {
    GtkWidget *dialog;
    GtkFileChooserAction action = GTK_FILE_CHOOSER_ACTION_OPEN;
    gint res;

    dialog = gtk_file_chooser_dialog_new("Open File", GTK_WINDOW(user_data), action,
                                        "_Cancel", GTK_RESPONSE_CANCEL,
                                        "_Open", GTK_RESPONSE_ACCEPT,
                                        NULL);

    res = gtk_dialog_run(GTK_DIALOG(dialog));
    if (res == GTK_RESPONSE_ACCEPT) {
        char *filename;
        GtkTextIter start_iter, end_iter;
        gchar *contents;
        gsize length;
        GError *error = NULL;

        filename = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog));
        g_file_get_contents(filename, &contents, &length, &error);
        g_free(filename);

        if (error) {
            GtkWidget *error_dialog = gtk_message_dialog_new(GTK_WINDOW(user_data),
                                                            GTK_DIALOG_DESTROY_WITH_PARENT,
                                                            GTK_MESSAGE_ERROR,
                                                            GTK_BUTTONS_CLOSE,
                                                            "Error opening file: %s", error->message);
            gtk_dialog_run(GTK_DIALOG(error_dialog));
            gtk_widget_destroy(error_dialog);
            g_error_free(error);
        } else {
            gtk_text_buffer_get_bounds(buffer, &start_iter, &end_iter);
            gtk_text_buffer_delete(buffer, &start_iter, &end_iter);
            gtk_text_buffer_insert(buffer, &start_iter, contents, -1);
            g_free(contents);
        }
    }

    gtk_widget_destroy(dialog);
}

static void on_save_activate(GtkMenuItem *menu_item, gpointer user_data) {
    GtkWidget *dialog;
    GtkFileChooserAction action = GTK_FILE_CHOOSER_ACTION_SAVE;
    gint res;

    dialog = gtk_file_chooser_dialog_new("Save File", GTK_WINDOW(user_data), action,
                                        "_Cancel", GTK_RESPONSE_CANCEL,
                                        "_Save", GTK_RESPONSE_ACCEPT,
                                        NULL);

    res = gtk_dialog_run(GTK_DIALOG(dialog));
    if (res == GTK_RESPONSE_ACCEPT) {
        char *filename;
        GtkTextIter start_iter, end_iter;
        gchar *contents;
        GError *error = NULL;

        filename = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog));
        gtk_text_buffer_get_bounds(buffer, &start_iter, &end_iter);
        contents = gtk_text_buffer_get_text(buffer, &start_iter, &end_iter, FALSE);

        g_file_set_contents(filename, contents, -1, &error);
        g_free(filename);
        g_free(contents);

        if (error) {
            GtkWidget *error_dialog = gtk_message_dialog_new(GTK_WINDOW(user_data),
                                                            GTK_DIALOG_DESTROY_WITH_PARENT,
                                                            GTK_MESSAGE_ERROR,
                                                            GTK_BUTTONS_CLOSE,
                                                            "Error saving file: %s", error->message);
            gtk_dialog_run(GTK_DIALOG(error_dialog));
            gtk_widget_destroy(error_dialog);
            g_error_free(error);
        }
    }

    gtk_widget_destroy(dialog);
}

int main(int argc, char *argv[]) {
    GtkWidget *window;
    GtkWidget *header_bar;
    GtkWidget *menu_button;
    GtkWidget *menu;
    GtkWidget *menu_item;
    GtkWidget *scrolled_window;
    GtkWidget *text_area_box;

    gtk_init(&argc, &argv);

    window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Text Editor with Line Numbers");
    gtk_window_set_default_size(GTK_WINDOW(window), 600, 400);
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);

    g_signal_connect(window, "destroy", G_CALLBACK(gtk_main_quit), NULL);

    header_bar = gtk_header_bar_new();
    gtk_header_bar_set_show_close_button(GTK_HEADER_BAR(header_bar), TRUE);
    gtk_header_bar_set_title(GTK_HEADER_BAR(header_bar), "Text Editor");

    gtk_window_set_titlebar(GTK_WINDOW(window), header_bar);

    menu_button = gtk_menu_button_new();
    gtk_header_bar_pack_start(GTK_HEADER_BAR(header_bar), menu_button);

    menu = gtk_menu_new();

    menu_item = gtk_menu_item_new_with_label("New");
    g_signal_connect(menu_item, "activate", G_CALLBACK(on_new_activate), window);
    gtk_menu_shell_append(GTK_MENU_SHELL(menu), menu_item);

    menu_item = gtk_menu_item_new_with_label("Open");
    g_signal_connect(menu_item, "activate", G_CALLBACK(on_open_activate), window);
    gtk_menu_shell_append(GTK_MENU_SHELL(menu), menu_item);

    menu_item = gtk_menu_item_new_with_label("Save");
    g_signal_connect(menu_item, "activate", G_CALLBACK(on_save_activate), window);
    gtk_menu_shell_append(GTK_MENU_SHELL(menu), menu_item);

    menu_item = gtk_menu_item_new_with_label("Quit");
    g_signal_connect(menu_item, "activate", G_CALLBACK(gtk_main_quit), NULL);
    gtk_menu_shell_append(GTK_MENU_SHELL(menu), menu_item);

    gtk_widget_show_all(menu);

    gtk_menu_button_set_popup(GTK_MENU_BUTTON(menu_button), GTK_WIDGET(menu));

    text_view = gtk_text_view_new();
    buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(text_view));
    gtk_text_view_set_wrap_mode(GTK_TEXT_VIEW(text_view), GTK_WRAP_WORD);

    scrolled_window = gtk_scrolled_window_new(NULL, NULL);
    gtk_container_add(GTK_CONTAINER(scrolled_window), text_view);

    line_number_area = gtk_drawing_area_new();
    gtk_widget_set_size_request(line_number_area, 40, -1);

    g_signal_connect(line_number_area, "draw", G_CALLBACK(draw_line_numbers), NULL);
    g_signal_connect(buffer, "changed", G_CALLBACK(on_text_change), line_number_area);

    vadj = gtk_scrolled_window_get_vadjustment(GTK_SCROLLED_WINDOW(scrolled_window));
    g_signal_connect(vadj, "value-changed", G_CALLBACK(on_vadj_changed), line_number_area);

    text_area_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_box_pack_start(GTK_BOX(text_area_box), line_number_area, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(text_area_box), scrolled_window, TRUE, TRUE, 0);

    gtk_container_add(GTK_CONTAINER(window), text_area_box);

    gtk_widget_show_all(window);

    gtk_main();

    return 0;
}
