#include <gtk/gtk.h>

GtkWidget *text_view;
GtkWidget *line_number_area;
GtkTextBuffer *buffer;

static void draw_line_numbers(GtkWidget *widget, cairo_t *cr, gpointer user_data) {
    GtkTextIter start_iter, end_iter;
    gint line_number = 1;
    gint y_offset = 0;
    gchar *line_text;
    gint line_length;

    cairo_set_source_rgb(cr, 0.5, 0.5, 0.5);

    gtk_text_buffer_get_bounds(buffer, &start_iter, &end_iter);

    while (gtk_text_iter_forward_line(&start_iter)) {
        line_text = gtk_text_buffer_get_text(buffer, &start_iter, &end_iter, FALSE);
        line_length = strlen(line_text);
        if (line_length > 0) {

            cairo_move_to(cr, 5, y_offset + 15); 
            cairo_show_text(cr, g_strdup_printf("%d", line_number));
            y_offset += 18;  
            line_number++;
        }
        g_free(line_text);
    }
}

int main(int argc, char *argv[]) {
    GtkWidget *window;
    GtkWidget *header_bar;
    GtkWidget *menu_button;
    GtkWidget *menu;
    GtkWidget *menu_item;
    GtkWidget *scrolled_window;
    GtkWidget *text_area_box;
    GtkWidget *line_number_area;
    
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
    gtk_menu_shell_append(GTK_MENU_SHELL(menu), menu_item);

    menu_item = gtk_menu_item_new_with_label("Open");
    gtk_menu_shell_append(GTK_MENU_SHELL(menu), menu_item);

    menu_item = gtk_menu_item_new_with_label("Save");
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

    text_area_box = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 0);
    gtk_box_pack_start(GTK_BOX(text_area_box), line_number_area, FALSE, FALSE, 0);
    gtk_box_pack_start(GTK_BOX(text_area_box), scrolled_window, TRUE, TRUE, 0);


    gtk_container_add(GTK_CONTAINER(window), text_area_box);

    gtk_widget_show_all(window);

    gtk_main();

    return 0;
}
