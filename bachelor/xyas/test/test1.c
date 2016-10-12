#include <stdio.h>
#include <stdlib.h>
#include <gtk/gtk.h>

static GtkWidget *view = NULL;

void enter_callback( GtkWidget *widget,
                     GtkWidget *entry )
{
  const gchar *entry_text;
  entry_text = gtk_entry_get_text (GTK_ENTRY (entry));
  printf("Entry contents: %s\n", entry_text);
}

void entry_toggle_editable( GtkWidget *checkbutton,
                            GtkWidget *entry )
{
  gtk_editable_set_editable (GTK_EDITABLE (entry),
                             GTK_TOGGLE_BUTTON (checkbutton)->active);
}

void entry_toggle_visibility( GtkWidget *checkbutton,
                              GtkWidget *entry )
{
  gtk_entry_set_visibility (GTK_ENTRY (entry),
             GTK_TOGGLE_BUTTON (checkbutton)->active);
}

static void get_all_text(void) {
	GtkTextIter start, end;
	GtkTextMark *mark = NULL;
	GtkTextBuffer *buffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW (view));
	//mark = gtk_text_buffer_get_selection_bound(buffer);
	gtk_text_buffer_get_start_iter(buffer, &start);
	//mark = gtk_text_buffer_get_mark(buffer, "insert");
	gtk_text_buffer_get_end_iter(buffer, &end);
	gchar *text = gtk_text_iter_get_text(&start, &end);
	g_message("text is [%s]", text);
	return ;
}

int main( int argc,
          char *argv[] )
{

    GtkWidget *window;
    GtkWidget *vbox, *hbox;
    GtkWidget *entry;
    GtkWidget *table;
    GtkWidget *check;
    gint tmp_pos;

    gtk_init (&argc, &argv);

    /* 创建一个新窗口 */
    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    gtk_widget_set_size_request (GTK_WIDGET (window), 500, 500);
    gtk_window_set_title (GTK_WINDOW (window), "GTK Entry");
    g_signal_connect (G_OBJECT (window), "destroy",
                      G_CALLBACK (gtk_main_quit), NULL);
    g_signal_connect_swapped (G_OBJECT (window), "delete_event",
                              G_CALLBACK (gtk_widget_destroy), 
                              window);
	table = gtk_table_new(20, 20, FALSE);
	gtk_table_set_row_spacings(GTK_TABLE (table), 20);
	gtk_table_set_col_spacings(GTK_TABLE (table), 20);
	GtkWidget *submit = gtk_button_new_with_label("submit");
//	vbox = gtk_vbox_new(FALSE, 0);
	view = gtk_text_view_new();
	gtk_text_view_set_editable(GTK_TEXT_VIEW (view), TRUE);
	gtk_table_attach_defaults(GTK_TABLE (table), view, 0, 20, 0, 18);
	gtk_table_attach_defaults(GTK_TABLE (table), submit, 19, 20, 19, 20);
//	gtk_box_pack_start(GTK_BOX (vbox), view, TRUE, TRUE, 0);
	gtk_container_add(GTK_CONTAINER (window), table);
    g_signal_connect (G_OBJECT (submit), "clicked", G_CALLBACK (get_all_text), NULL);
#if 0
    vbox = gtk_vbox_new (FALSE, 0);
    gtk_container_add (GTK_CONTAINER (window), vbox);
    gtk_widget_show (vbox);

    entry = gtk_entry_new ();
    gtk_entry_set_max_length (GTK_ENTRY (entry), 50);
    g_signal_connect (G_OBJECT (entry), "activate",
         G_CALLBACK (enter_callback),
         entry);
    gtk_entry_set_text (GTK_ENTRY (entry), "hello");
    tmp_pos = GTK_ENTRY (entry)->text_length;
    gtk_editable_insert_text (GTK_EDITABLE (entry), " world", -1, &tmp_pos);
    gtk_editable_select_region (GTK_EDITABLE (entry),
             0, GTK_ENTRY (entry)->text_length);
    gtk_box_pack_start (GTK_BOX (vbox), entry, TRUE, TRUE, 0);
    gtk_widget_show (entry);
#endif
#if 0
    hbox = gtk_hbox_new (FALSE, 0);
    gtk_container_add (GTK_CONTAINER (vbox), hbox);
    gtk_box_pack_start (GTK_BOX (hbox), entry, TRUE, TRUE, 0);
    gtk_widget_show (hbox);
#endif
#if 0
    check = gtk_check_button_new_with_label ("Editable");
    gtk_box_pack_start (GTK_BOX (hbox), check, TRUE, TRUE, 0);
    g_signal_connect (G_OBJECT (check), "toggled",
     G_CALLBACK (entry_toggle_editable), entry);
    gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (check), TRUE);
    gtk_widget_show (check);
    
    check = gtk_check_button_new_with_label ("Visible");
    gtk_box_pack_start (GTK_BOX (hbox), check, TRUE, TRUE, 0);
    g_signal_connect (G_OBJECT (check), "toggled",
     G_CALLBACK (entry_toggle_visibility), entry);
    gtk_toggle_button_set_active (GTK_TOGGLE_BUTTON (check), TRUE);
    gtk_widget_show (check);
                                   
    button = gtk_button_new_from_stock (GTK_STOCK_CLOSE);
    g_signal_connect_swapped (G_OBJECT (button), "clicked",
             G_CALLBACK (gtk_widget_destroy),
             window);
    gtk_box_pack_start (GTK_BOX (vbox), button, TRUE, TRUE, 0);
    GTK_WIDGET_SET_FLAGS (button, GTK_CAN_DEFAULT);
    gtk_widget_grab_default (button);
    gtk_widget_show (button);
#endif
    gtk_widget_show_all (GTK_WIDGET (window));

    gtk_main();

    return 0;
}
