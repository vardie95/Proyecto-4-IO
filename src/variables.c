#include <gtk/gtk.h>

GtkWidget       *variablesW;



GtkWidget *gTextName;
GtkWidget *gComboValuesItem;
GtkBuilder      *builder; 

int main(int argc, char *argv[])
{
    
 
    gtk_init(&argc, &argv);
 
    builder = gtk_builder_new();
    gtk_builder_add_from_file (builder, "glade/variables.glade", NULL);
    variablesW= GTK_WIDGET(gtk_builder_get_object(builder, "windows_var"));
    gtk_builder_connect_signals(builder, NULL);
    g_object_unref(builder);
    gtk_widget_show(variablesW);                
    gtk_main(); 
    return 0;
}



 
// called when window is closed
void on_window_main_destroy()
{
    gtk_main_quit();
}