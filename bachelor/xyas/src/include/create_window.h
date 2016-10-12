#ifndef __CREATE_WINDOW_H
#define __CREATE_WINDOW_H

#include <glib.h>
#include <gtk/gtk.h>

static int get_buff(void) {
	int check = 0;
	int i = 0;
	int result = 0;
	// get_text[0] is add, get_text[1] is delete, get_text[2] is alter, get_text[3] is search
	for (i = 0; i < ITEMS; i++) {
#if 0
		if (NULL != get_text[i] && (0 == check)) {
			g_message("length is %d", gtk_entry_get_text_length(GTK_ENTRY (text[i])));
			g_message("i is %d", i);
			g_message("77 dbg %s", get_text[i]);
			check = 1;
		} else if (NULL == get_text[i] && (0 == check)) {
			g_message("length is %d", gtk_entry_get_text_length(GTK_ENTRY (text[i])));
			g_message("i is %d", i);
			g_message("77 dbg %s", get_text[i]);
			continue;
		} else if (NULL != get_text[i] && (1 == check)) {
			g_message("length is %d", gtk_entry_get_text_length(GTK_ENTRY (text[i])));
			g_message("i is %d", i);
			g_message("77 dbg %s", get_text[i]);
			g_message("Error we just have one input");
			exit(-1);
		}
#endif
		if (0 != gtk_entry_get_text_length(GTK_ENTRY (text[i])) && (0 == check)) {
			check = 1;
			get_text[i] = gtk_entry_get_text (GTK_ENTRY (text[i]));
			result = i;
		} else if (0 != gtk_entry_get_text_length(GTK_ENTRY (text[i])) && (1 == check)) {
			g_message("Error we just have only one option a time!!!");
			exit(-1);
		}
		printf("Entry contents: %s\n", get_text[i]);
	}
	return result;
}

static void delete_hism(GtkWidget *widget, gpointer data) {
	gtk_main_quit();
	return ;
}

static void delete_add(GtkWidget *widget, gpointer data) {
	gtk_widget_destroy(GTK_WIDGET (add_window));
	return ;
}

static void print(void) {
	table = gtk_table_new(20, 3, FALSE);
	gtk_table_set_row_spacings(GTK_TABLE (table), 10);
	gtk_table_set_col_spacings(GTK_TABLE (table), 10);
	gtk_container_add(GTK_CONTAINER (window), table);
	label = gtk_label_new("add algorithm: ");
	gtk_table_attach_defaults(GTK_TABLE (table), label, 7, 8, 7, 8);
	gtk_misc_set_alignment(GTK_MISC (label), 0, 0);
	label = gtk_label_new("delete algorithm: ");
	gtk_table_attach_defaults(GTK_TABLE (table), label, 7, 8, 8, 9);
	gtk_misc_set_alignment(GTK_MISC (label), 0, 0);
	label = gtk_label_new("alter algorithm: ");
	gtk_table_attach_defaults(GTK_TABLE (table), label, 7, 8, 9, 10);
	gtk_misc_set_alignment(GTK_MISC (label), 0, 0);
	label = gtk_label_new("search algorithm: ");
	gtk_table_attach_defaults(GTK_TABLE (table), label, 7, 8, 10, 11);
	gtk_misc_set_alignment(GTK_MISC (label), 0, 0);
}

static void input(void) {
	int i = 0;
	int top = 7;
	int bot = 8;

	while (i < 4) {
		text[i] = gtk_entry_new();
		gtk_table_attach_defaults(GTK_TABLE (table), text[i], 8, 9, top, bot);
		top += 1;
		bot += 1;
		i += 1;
	}
}

static void print_help(void) {
	GtkWidget *error_window = g_object_new(GTK_TYPE_WINDOW, 
				"title", "Help Info", 
				"default_height", 100,
				"default_width", 100,
				NULL);
	gtk_container_border_width(GTK_CONTAINER(error_window), 10);
	g_signal_connect(add_window, "destroy", G_CALLBACK(delete_hism), NULL);
	GtkWidget *error_table = gtk_table_new(20, 20, FALSE);
	GtkWidget *error_label = gtk_label_new("This is XYAS, see code.google.com/p/xyas for details ;-)");
	gtk_table_attach_defaults(GTK_TABLE (error_table), error_label, 0, 20, 0, 20);
	gtk_container_add(GTK_CONTAINER (error_window), error_table);
	gtk_widget_show_all(GTK_WIDGET (error_window));
	gtk_main();
	return ;
}

static void print_help_info(void) {
}

static void destroy(void) {
	gtk_main_quit();
	return ;
}

static void print_buttons(void) {
	submit_button = gtk_button_new_with_label("submit");
	gtk_table_attach_defaults(GTK_TABLE (table), submit_button, 17, 18, 17, 18);
//	g_signal_connect(G_OBJECT (submit_button), "clicked", G_CALLBACK (get_buff), NULL);
	help_button = gtk_button_new_with_label("help");
	gtk_table_attach_defaults(GTK_TABLE (table), help_button, 17, 18, 18, 19);
	g_signal_connect(G_OBJECT (help_button), "clicked", G_CALLBACK (print_help), NULL);
	exit_button = gtk_button_new_with_label("exit");
	gtk_table_attach_defaults(GTK_TABLE (table), exit_button, 17, 18, 19, 20);
	g_signal_connect(G_OBJECT (exit_button), "clicked", G_CALLBACK (destroy), NULL);
}

static void create_window(void) {
	int i = 0;

	window = g_object_new(GTK_TYPE_WINDOW, 
				"title", "XY Algorithm Search", 
				"default_height", window_height,
				"default_width", window_width,
				NULL);
	gtk_container_border_width(GTK_CONTAINER(window), 10);
	g_signal_connect(window, "destroy", G_CALLBACK(delete_hism), NULL);
	print();
	input();
	print_buttons();
	return ;
}

static void
create_algo_window(void) {
	algo_window = g_object_new(GTK_TYPE_WINDOW, 
				"title", "XY Algorithm Search", 
				"default_height", window_height,
				"default_width", window_width,
				NULL);
	gtk_container_border_width(GTK_CONTAINER(algo_window), 10);
	g_signal_connect(algo_window, "destroy", G_CALLBACK(delete_hism), NULL);
	algo_table = gtk_table_new(window_height, window_width, FALSE);
//	gtk_table_set_row_spacings(GTK_TABLE (algo_table), window_width);
//	gtk_table_set_col_spacings(GTK_TABLE (algo_table), window_height);
	gtk_container_add(GTK_CONTAINER (algo_window), algo_table);
	algo_label = gtk_label_new(NULL);
	gtk_table_attach_defaults(GTK_TABLE (algo_table), algo_label, 0, window_height - 1, 0, window_width - 1);
}

static void get_all_text(void) {
	GtkTextIter start, end;
	GtkTextMark *mark = NULL;
	GtkTextBuffer *buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW (add_view));
	//mark = gtk_text_buffer_get_selection_bound(buffer);
	gtk_text_buffer_get_start_iter(buffer, &start);
	//mark = gtk_text_buffer_get_mark(buffer, "insert");
	gtk_text_buffer_get_end_iter(buffer, &end);
	add_text = gtk_text_iter_get_text(&start, &end);
	g_message("text is [%s]", add_text);
	return ;
}


static void
create_add_window(void) {
	add_window = g_object_new(GTK_TYPE_WINDOW, 
				"title", "XY Algorithm Search", 
				"default_height", window_height,
				"default_width", window_width,
				NULL);
	gtk_container_border_width(GTK_CONTAINER(add_window), 10);
	g_signal_connect(add_window, "destroy", G_CALLBACK(delete_hism), NULL);
	g_signal_connect_swapped (G_OBJECT (add_window), "delete_event",
                              G_CALLBACK (gtk_widget_destroy), 
                              add_window);
	add_table = gtk_table_new(20, 20, FALSE);
	gtk_table_set_row_spacings(GTK_TABLE (add_table), 20);
	gtk_table_set_col_spacings(GTK_TABLE (add_table), 20);
	add_submit = gtk_button_new_with_label("submit");
//	vbox = gtk_vbox_new(FALSE, 0);
	add_view = gtk_text_view_new();
	gtk_text_view_set_editable(GTK_TEXT_VIEW (add_view), TRUE);
	gtk_table_attach_defaults(GTK_TABLE (add_table), add_view, 0, 20, 0, 18);
	gtk_table_attach_defaults(GTK_TABLE (add_table), add_submit, 19, 20, 19, 20);
//	gtk_box_pack_start(GTK_BOX (vbox), view, TRUE, TRUE, 0);
	gtk_container_add(GTK_CONTAINER (add_window), add_table);
    g_signal_connect (G_OBJECT (add_submit), "clicked", G_CALLBACK (get_all_text), NULL);
	gtk_widget_show_all(GTK_WIDGET (add_window));
	gtk_main();
	return ;
}

static void print_error(void) {
	GtkWidget *error_window = g_object_new(GTK_TYPE_WINDOW, 
				"title", "ERROR", 
				"default_height", 100,
				"default_width", 100,
				NULL);
	gtk_container_border_width(GTK_CONTAINER(error_window), 10);
	g_signal_connect(add_window, "destroy", G_CALLBACK(delete_hism), NULL);
	GtkWidget *error_table = gtk_table_new(20, 20, FALSE);
	GtkWidget *error_label = gtk_label_new("We can not find your algorithm, please try again!!!");
	gtk_table_attach_defaults(GTK_TABLE (error_table), error_label, 0, 20, 0, 20);
	gtk_container_add(GTK_CONTAINER (error_window), error_table);
	gtk_widget_show_all(GTK_WIDGET (error_window));
	gtk_main();
	return ;
}

static void get_alter_text(void) {
	GtkTextIter start, end;
	GtkTextMark *mark = NULL;
	GtkTextBuffer *buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW (alter_view));
	//mark = gtk_text_buffer_get_selection_bound(buffer);
	gtk_text_buffer_get_start_iter(buffer, &start);
	//mark = gtk_text_buffer_get_mark(buffer, "insert");
	gtk_text_buffer_get_end_iter(buffer, &end);
	alter_text = gtk_text_iter_get_text(&start, &end);
	g_message("text is [%s]", alter_text);
	return ;
}


static void
create_alter_window(void) {
	alter_window = g_object_new(GTK_TYPE_WINDOW, 
				"title", "XY Algorithm Search", 
				"default_height", window_height,
				"default_width", window_width,
				NULL);
	gtk_container_border_width(GTK_CONTAINER(alter_window), 10);
	g_signal_connect(alter_window, "destroy", G_CALLBACK(delete_hism), NULL);
	g_signal_connect_swapped (G_OBJECT (alter_window), "delete_event",
                              G_CALLBACK (gtk_widget_destroy), 
                              alter_window);
	alter_table = gtk_table_new(20, 20, FALSE);
	gtk_table_set_row_spacings(GTK_TABLE (alter_table), 20);
	gtk_table_set_col_spacings(GTK_TABLE (alter_table), 20);
	alter_submit = gtk_button_new_with_label("submit");
//	vbox = gtk_vbox_new(FALSE, 0);
	alter_view = gtk_text_view_new();
	gtk_text_view_set_editable(GTK_TEXT_VIEW (alter_view), TRUE);
//	GtkTextBuffer *tmp_buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW (alter_view));
//	GtkTextIter *iter = NULL;
//	gtk_text_buffer_get_iter_at_offset(tmp_buffer, iter, 0);
//	gtk_text_buffer_insert(tmp_buffer, iter, alter, strlen(alter));
	gtk_table_attach_defaults(GTK_TABLE (alter_table), alter_view, 0, 20, 0, 18);
	gtk_table_attach_defaults(GTK_TABLE (alter_table), alter_submit, 19, 20, 19, 20);
//	gtk_box_pack_start(GTK_BOX (vbox), view, TRUE, TRUE, 0);
	gtk_container_add(GTK_CONTAINER (alter_window), alter_table);
    g_signal_connect (G_OBJECT (alter_submit), "clicked", G_CALLBACK (get_alter_text), NULL);
	gtk_widget_show_all(GTK_WIDGET (alter_window));
	gtk_main();
	return ;
}

#endif
