#include <gtk/gtk.h>

void end_program(GtkWidget *wid, gpointer ptr){
    gtk_main_quit();
}

int main(int argc,char *argv[]){
    GtkWidget *win = gtk_window_new (GTK_WINDOW_TOPLEVEL);  
    GtkWidget *btn = gtk_button_new_with_label ("Close window");
    GtkWidget *lbl = gtk_label_new ("My label");
    GtkWidget *box = gtk_vbox_new(FALSE,5);

    gtk_init (&argc, &argv);
    g_signal_connect(btn,"clicked",G_CALLBACK(end_program), NULL);
    g_signal_connect(win,"delete_event",G_CALLBACK(end_program), NULL);

    gtk_box_pack_start(GTK_BOX(box),lbl,TRUE,TRUE,0);
    gtk_box_pack_start(GTK_BOX(box),btn,TRUE,TRUE,0);

    gtk_container_add(GTK_CONTAINER(win),box);
    
    gtk_widget_show_all (win);
    gtk_main();
}