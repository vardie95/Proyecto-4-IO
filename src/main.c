#include <gtk/gtk.h>

GtkWidget       *mainW;
GtkWidget       *VariablesW;


GtkWidget *gTextName;
GtkWidget *gComboValuesItem;
GtkBuilder      *builder; 

int main(int argc, char *argv[])
{
    
 
    gtk_init(&argc, &argv);
 
    builder = gtk_builder_new();
    gtk_builder_add_from_file (builder, "glade/main.glade", NULL);
 
    mainW= GTK_WIDGET(gtk_builder_get_object(builder, "window_main"));
    gtk_builder_connect_signals(builder, NULL);
    VariablesW= GTK_WIDGET(gtk_builder_get_object(builder, "window_var"));
    gTextName = GTK_WIDGET(gtk_builder_get_object(builder, "TFName"));
    gComboValuesItem = GTK_WIDGET(gtk_builder_get_object(builder, "CBVariables"));
    g_object_unref(builder);
    gtk_widget_show(mainW);                
    gtk_main();
 
    return 0;
}

void on_BTNAceptar_clicked() {
            const gchar* texto;
            const gchar* selectVariables;
            texto = gtk_entry_get_text(GTK_ENTRY(gTextName));
            printf("%s\n",texto);
            selectVariables = gtk_combo_box_text_get_active_text (GTK_COMBO_BOX_TEXT(gComboValuesItem));
            printf("%s\n",selectVariables);
            if ((texto == NULL) || (texto[0] == '\0')) {
                    GtkWidget* dialog;
                    GtkDialogFlags flags = GTK_DIALOG_DESTROY_WITH_PARENT;
                    dialog = gtk_message_dialog_new (GTK_WINDOW(mainW),flags,GTK_MESSAGE_ERROR,
                                 GTK_BUTTONS_CLOSE,
                                 "Error: Digite un nombre de problema");
gtk_dialog_run (GTK_DIALOG (dialog));
gtk_widget_destroy (dialog);
            }else{
                gtk_widget_show(VariablesW); 
                gtk_widget_hide(mainW);
            }
            
}

 
// called when window is closed
void on_window_main_destroy()
{
    gtk_main_quit();
}