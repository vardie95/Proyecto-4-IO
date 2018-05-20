#include <gtk/gtk.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "components/simplex.c"
GtkWidget       *mainW;
GtkWidget       *gTextName;
GtkWidget       *gComboVarItem;
GtkWidget       *gComboResItem;
GtkBuilder      *builder;

GtkWidget       *VariablesW;
GtkWidget       ***initialTable;
GtkWidget       *tableData;
GtkWidget       *containerTable;

GtkWidget       *FuncionW;
GtkWidget       ***initialTableFunc;
GtkWidget       *tableDataFunc;
GtkWidget       *containerTableFunc;

GtkWidget       *RestrictionW;
GtkWidget       ***initialTableRes;
GtkWidget       *tableDataRes;
GtkWidget       *containerTableRes;




int selectVariables;
int selectRestricciones;
const char *rowHeader[2] = {"Variables"};

const char *tablenameVar;
int *FunctionTable;
int **RestrictionTable;

int main(int argc, char *argv[])
{


    gtk_init(&argc, &argv);

    builder = gtk_builder_new();
    gtk_builder_add_from_file (builder, "glade/main.glade", NULL);

    mainW= GTK_WIDGET(gtk_builder_get_object(builder, "window_main"));

    gTextName = GTK_WIDGET(gtk_builder_get_object(builder, "TFName"));
    gComboVarItem = GTK_WIDGET(gtk_builder_get_object(builder, "CBVariables"));
    gtk_spin_button_set_range (GTK_SPIN_BUTTON(gComboVarItem),1,8);
    gtk_spin_button_set_increments (GTK_SPIN_BUTTON(gComboVarItem),1,1);

    gComboResItem= GTK_WIDGET(gtk_builder_get_object(builder, "CBRestricciones"));
    gtk_spin_button_set_range (GTK_SPIN_BUTTON(gComboResItem),1,10);
    gtk_spin_button_set_increments (GTK_SPIN_BUTTON(gComboResItem),1,1);

    VariablesW= GTK_WIDGET(gtk_builder_get_object(builder, "window_var"));
    gtk_builder_connect_signals(builder, NULL);
    containerTable = GTK_WIDGET(gtk_builder_get_object(builder, "containerTable"));
    gtk_builder_connect_signals(builder, NULL);

    FuncionW= GTK_WIDGET(gtk_builder_get_object(builder, "window_fun"));
    gtk_builder_connect_signals(builder, NULL);
    containerTableFunc = GTK_WIDGET(gtk_builder_get_object(builder, "containerFuntionTable"));
    gtk_builder_connect_signals(builder, NULL);

    RestrictionW= GTK_WIDGET(gtk_builder_get_object(builder, "window_res"));
    gtk_builder_connect_signals(builder, NULL);
    containerTableRes = GTK_WIDGET(gtk_builder_get_object(builder, "containerRestTable"));
    gtk_builder_connect_signals(builder, NULL);


    gtk_builder_connect_signals(builder, NULL);
    g_object_unref(builder);
    gtk_widget_show(mainW);
    gtk_main();

    pruebaSimplex();
    return 0;
}

void pruebaSimplex()
{
  int m = 3;
  int n = 6;
  double** table;
  table = (double**) malloc(sizeof(double *) * m);
  for (int i = 0; i < n; i++)
	{
		table[i] = (double*) malloc(sizeof(double) * n);
	}
  // simplex -------------------------------------------------------------------
  table[0][0]=1.0;table[0][1]=-3.0;table[0][2]=-4.0;table[0][3]=0.0;table[0][4]=0.0;table[0][5]=0.0;
  table[1][0]=0.0;table[1][1]=1.0;table[1][2]=1.0;table[1][3]=1.0;table[1][4]=0.0;table[1][5]=40.0;
  table[2][0]=0.0;table[2][1]=1.0;table[2][2]=2.0;table[2][3]=0.0;table[2][4]=1.0;table[2][5]=60.0;
  simplex(table, m, n, false);
}

void createSetNodeData()
{
  int keys = selectVariables;
  initialTable = calloc(keys,sizeof(GtkWidget**));
  char columnVarName[4];

  tableData = gtk_grid_new ();
  gtk_container_add (GTK_CONTAINER (containerTable), tableData);

  for(int j = 0; j < keys; j++) {
    initialTable[j] = calloc(2,sizeof(GtkWidget*));
  }

  for(int row =0; row < keys; row++)
  {
    for(int column=0; column < 2; column++)
    {
      if (column == 0){
        initialTable[row][column] = gtk_entry_new();
        gtk_entry_set_width_chars(GTK_ENTRY(initialTable[row][column]),10);
        gtk_grid_attach (GTK_GRID (tableData),initialTable[row][column] , column, row, 1, 1);
      } else{

        initialTable[row][column] = gtk_entry_new();
        gtk_entry_set_width_chars(GTK_ENTRY(initialTable[row][column]),50);
        gtk_grid_attach (GTK_GRID (tableData),initialTable[row][column] , column, row, 1, 1);
      }

      if (column == 0){
        sprintf(columnVarName, "X%d", row + 1);
        gtk_entry_set_text (GTK_ENTRY(initialTable[row][column]),columnVarName);
        gtk_widget_set_name(initialTable[row][column],"header");
        gtk_widget_set_sensitive(initialTable[row][column],FALSE);
      }
    }
  }

}

void createSetNodeDataFuntion(){
  int keys = selectVariables;
  initialTableFunc = calloc(10,sizeof(GtkWidget**));
  char columnVarName[4];

  tableDataFunc = gtk_grid_new ();
  gtk_container_add (GTK_CONTAINER (containerTableFunc), tableDataFunc);

  for(int j = 0; j < keys + 1; j++) {
    initialTableFunc[j] = calloc(2,sizeof(GtkWidget*));
  }

  for(int row =0; row < 2; row++)
  {
    for(int column=0; column < keys ; column++)
    {
        initialTableFunc[row][column] = gtk_entry_new();
        gtk_entry_set_width_chars(GTK_ENTRY(initialTableFunc[row][column]),9);
        gtk_grid_attach (GTK_GRID (tableDataFunc),initialTableFunc[row][column] , column, row, 1, 1);
       
      if (row == 0){
        sprintf(columnVarName, "X%d", column + 1);
        gtk_entry_set_text (GTK_ENTRY(initialTableFunc[row][column]),columnVarName);
        gtk_widget_set_name(initialTableFunc[row][column],"header");
        gtk_widget_set_sensitive(initialTableFunc[row][column],FALSE);
      }
    }
  }

}

void createSetNodeDataRestriccion(){
  int keys = selectVariables;
  int rest = selectRestricciones;
  initialTableRes = calloc(13,sizeof(GtkWidget**));
  char columnVarName[4];

  tableDataRes = gtk_grid_new ();
  gtk_container_add (GTK_CONTAINER (containerTableRes), tableDataRes);

  for(int j = 0; j < keys + 4; j++) {
    initialTableRes[j] = calloc(13,sizeof(GtkWidget*));
  }

  for(int row =0; row < rest +1; row++)
  {
    for(int column=0; column < keys + 2 ; column++)
    {
        initialTableRes[row][column] = gtk_entry_new();
        gtk_entry_set_width_chars(GTK_ENTRY(initialTableRes[row][column]),9);
        gtk_grid_attach (GTK_GRID (tableDataRes),initialTableRes[row][column] , column, row, 1, 1);
       
      if (row == 0){
      	if( column == keys ){
        	sprintf(columnVarName, "R");
    	}else if (column == keys + 1 ){
    		sprintf(columnVarName, " ");
    	}else{
    		sprintf(columnVarName, "X%d", column + 1);
    	}
        gtk_entry_set_text (GTK_ENTRY(initialTableRes[row][column]),columnVarName);
        gtk_widget_set_name(initialTableRes[row][column],"header");
        gtk_widget_set_sensitive(initialTableRes[row][column],FALSE);
      }
      if (column == keys && row != 0){
      	sprintf(columnVarName, "=");
      	gtk_entry_set_text (GTK_ENTRY(initialTableRes[row][column]),columnVarName);
      }
    }
  }

}



void getNombresVar(){
    ///r_table =(char*)malloc ( selectVariables * sizeof (char));
    const gchar* texto;
    for(int i = 0; i < selectVariables;i++){
        texto = gtk_entry_get_text(GTK_ENTRY(initialTable[i][1]));
        //sprintf(tablenameVar[i][0], "%s\n", texto);
        ///sprintf("%s\n",texto);

    }


}

void getFuntionNumber(){
    FunctionTable = malloc(sizeof(float *) * selectVariables);

    int number;
    for(int i = 0; i < selectVariables;i++){
        FunctionTable[i] = atoi(gtk_entry_get_text(GTK_ENTRY(initialTableFunc[1][i])));
        printf("%d\n",FunctionTable[i]);
    }
}

void getRestricNumber(){
	int keys = selectVariables;
  	int rest = selectRestricciones;
    RestrictionTable = malloc(sizeof(float *) * 14);
    printf("Restricciones\n");
    for (int i = 0; i < 14; i++)
	{
		RestrictionTable[i] = malloc(sizeof(float) * 14);

	}

    int number;
    for(int i = 1; i < selectRestricciones + 1;i++){
    	 for(int j = 0; j < selectVariables + 2;j++){
    	 	if( j != selectVariables){
        		RestrictionTable[i][j] = atoi(gtk_entry_get_text(GTK_ENTRY(initialTableRes[i][j])));
        	printf("%d ",RestrictionTable[i][j]);
        	}
        	
    	}
    	printf(" \n");
    }
}

void on_BTNAceptar_clicked() {
            const gchar* texto;

            texto = gtk_entry_get_text(GTK_ENTRY(gTextName));
            ///printf("%s\n",texto);
            selectVariables = gtk_spin_button_get_value_as_int (GTK_SPIN_BUTTON(gComboVarItem));
            selectRestricciones = gtk_spin_button_get_value_as_int (GTK_SPIN_BUTTON(gComboResItem));
            //printf("%d\n",selectVariables);
            if ((texto == NULL) || (texto[0] == '\0')) {
                    GtkWidget* dialog;
                    GtkDialogFlags flags = GTK_DIALOG_DESTROY_WITH_PARENT;
                    dialog = gtk_message_dialog_new (GTK_WINDOW(mainW),flags,GTK_MESSAGE_ERROR,
                                 GTK_BUTTONS_CLOSE,
                                 "Error: Digite un nombre de problema");
gtk_dialog_run (GTK_DIALOG (dialog));
gtk_widget_destroy (dialog);
            }else{
                gtk_widget_hide(mainW);
                createSetNodeData();
                gtk_widget_show_all(VariablesW);

            }

}

void btnAceptarVar_clicked(){

    gtk_widget_hide(VariablesW);
    getNombresVar();
    createSetNodeDataFuntion();
    gtk_widget_show_all(FuncionW);
    free(initialTable);

}
void BTN_fun_Aceptar_clicked(){

    getFuntionNumber();
    gtk_widget_hide(FuncionW);
    createSetNodeDataRestriccion();
    gtk_widget_show_all(RestrictionW);
    free(initialTableFunc);


}
void btnAceptarRes_clicked(){
	free(initialTableFunc);
	getRestricNumber();
}



// called when window is closed
void on_window_main_destroy()
{

    gtk_main_quit();
}
