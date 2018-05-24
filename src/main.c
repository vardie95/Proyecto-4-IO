#include <gtk/gtk.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include "components/simplex.c"
#include "components/latex.c"

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
GtkWidget       *VerbContainer;

GtkWidget       *RestrictionW;
GtkWidget       ***initialTableRes;
GtkWidget       *tableDataRes;
GtkWidget       *containerTableRes;
GtkWidget 		*getIntermediateValue;




int selectVariables;
int selectRestricciones;
int verbSelect;
const char *rowHeader[2] = {"Variables"};

char tablenameVar[10];
double  FunctionTable[12];
double RestrictionTable[13][13];
int Restricciones[12];
int interTables;
int rows;
int columns;
int a_row = 0;
int a_column = 0;
bool big_m = false;

void buildTable();
void normal_simplex(double** table);
void big_m_simplex(double** table);
int getExtraVariablesColumns();

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

    VerbContainer = GTK_WIDGET(gtk_builder_get_object(builder, "comboVerb"));
    gtk_builder_connect_signals(builder, NULL);

    RestrictionW= GTK_WIDGET(gtk_builder_get_object(builder, "window_res"));
    gtk_builder_connect_signals(builder, NULL);
    containerTableRes = GTK_WIDGET(gtk_builder_get_object(builder, "containerRestTable"));
    gtk_builder_connect_signals(builder, NULL);

    getIntermediateValue = GTK_WIDGET(gtk_builder_get_object(builder, "check_Intermedias"));
    gtk_builder_connect_signals(builder, NULL);


    gtk_builder_connect_signals(builder, NULL);
    g_object_unref(builder);
    gtk_widget_show(mainW);
    gtk_main();
    return 0;
}

void buildTable()
{
  rows = 1 + selectRestricciones;
  columns = 1 + selectVariables + getExtraVariablesColumns() + 1;
  if (big_m == true)
  {
    rows += 1;
  }
  printf("Table[%d][%d]\n", rows, columns);
  double** table;
  table = (double**) malloc(sizeof(double *) * rows);
  for (int i = 0; i < rows; i++)
	{
		table[i] = (double*) malloc(sizeof(double) * columns);
	}
  printf("Holi\n");
  if (big_m == true)
  {
    big_m_simplex(table);
  }
  else
  {
    normal_simplex(table);
  }
}

int getArtVarPos()
{
  int temp = 0;
  for (int i = 1; i <= selectRestricciones; i++)
  {
    if (Restricciones[i] == 1) { temp += 1; }
    else if (Restricciones[i] == 2) { temp += 2; }
  }
  return temp;
}

void big_m_simplex(double** table)
{
  for (int j = 0; j < columns; j++)
  {
    if (j > selectVariables + getArtVarPos() - 1  && j < columns - 1)
    {
      table[0][j] = -1;
    }
    else
    {
      table[0][j] = 0;
    }
  }
  table[1][0] = 1;
  for (int i = 2; i < rows; i++) { table[i][0] = 0; }
  for (int j = 1; j < columns; j++)
  {
    if (j <= selectVariables)
    {
      if (verbSelect == 0) {
        table[1][j] = -1 * FunctionTable[j - 1];
      }
      else {
        table[1][j] = FunctionTable[j - 1];
      }
    }
    else { table[1][j] = 0; }
  }
  for (int i = 2; i < rows; i++)
  {
    for (int j = 1; j < columns; j++)
    {
      if (j <= selectVariables)
      {
        table[i][j] = RestrictionTable[i-1][j-1];
      }
      else if (j == columns - 1)
      {
        table[i][j] = RestrictionTable[i-1][selectVariables + 1];
      }
    }
  }
  print_table(table, rows, columns);

}

void normal_simplex(double** table)
{
  table[0][0] = 1;
  for (int i = 1; i < rows; i++) { table[i][0] = 0; }
  for (int j = 1; j < columns; j++)
  {
    if (j <= selectVariables)
    {
      if (verbSelect == 0) {
        table[0][j] = -1 * FunctionTable[j - 1];
      }
      else {
        table[0][j] = FunctionTable[j - 1];
      }
    }
    else { table [0][j] = 0; }
  }
  for (int i = 1; i < rows; i++)
  {
    for (int j = 1; j < columns; j++)
    {
      if (j <= selectVariables)
      {
        table[i][j] = RestrictionTable[i][j-1];
      }
      else if (j == columns - 1)
      {
        table[i][j] = RestrictionTable[i][selectVariables + 1];
      }
    }
  }
  int a = 0;
  int b = 0;
  for (int i = 1; i < rows; i++)
  {
    b = 0;
    for (int j = selectVariables + 1; j < columns - 1; j++)
    {
      if (a == b) {
        table[i][j] = 1;
      }
      b += 1;
    }
    a += 1;
  }
  if (verbSelect == 0)
  {
    simplex(table, rows, columns, false, true);
  }
  else
  {
    simplex(table, rows, columns, true, true);
  }

}

int getExtraVariablesColumns()
{
  int temp = 0;
  for (int i = 1; i <= selectRestricciones; i++)
  {
    if (Restricciones[i] == 0) { temp += 1; big_m = true;}
    else if (Restricciones[i] == 1) { temp += 1; }
    else if (Restricciones[i] == 2) { temp += 2; big_m = true; }
  }
  return temp;
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
    initialTableFunc[j] = calloc(10,sizeof(GtkWidget*));
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
    char ch[10];

    for(int i = 0; i < selectVariables-1;i++){
        texto = gtk_entry_get_text(GTK_ENTRY(initialTable[i][1]));
         sprintf(ch, "%8s\n", texto);
         tablenameVar[i]=ch;
		 ///sprintf(tablenameVar[i],texto);
         //printf("%s\n",tablenameVar[i]);

    }


}

void getFuntionNumber(){
	verbSelect = gtk_combo_box_get_active(GTK_COMBO_BOX(VerbContainer));
	printf("Verbo es: %d\n",verbSelect);
    for(int i = 0; i < selectVariables;i++){
        FunctionTable[i] = atof(gtk_entry_get_text(GTK_ENTRY(initialTableFunc[1][i])));
        printf("%f\n",FunctionTable[i]);
    }
}

void getRestricNumber(){
	int keys = selectVariables + 2;
  	int rest = selectRestricciones + 1 ;

    for(int i = 1; i < rest ;i++){
    	 for(int j = 0; j < keys;j++){
    	 	if( j != selectVariables){
        		RestrictionTable[i][j] = atof(gtk_entry_get_text(GTK_ENTRY(initialTableRes[i][j])));
        	  //printf("%f ",RestrictionTable[i][j]);
        	}

    	}
    	//printf(" \n");
    }
}

void getRestric(){
	const gchar* texto;
    for(int i = 1; i < selectRestricciones+1;i++){

        texto = gtk_entry_get_text(GTK_ENTRY(initialTableRes[i][selectVariables]));
        if (!(strcmp(texto,"="))){
        	Restricciones[i]= 0;
        	printf("%d\n", Restricciones[i]);
        }else if (!(strcmp(texto,"<="))) {
        	Restricciones[i]= 1;
        	printf("%d\n", Restricciones[i]);
        }else if (!(strcmp(texto,">="))){
        	Restricciones[i]= 2;
        	printf("%d\n", Restricciones[i]);
        }

    }




}

bool validarOperadores(){
	const gchar* texto;
	bool validar=true;
    for(int i = 1; i < selectRestricciones+1;i++){

        texto = gtk_entry_get_text(GTK_ENTRY(initialTableRes[i][selectVariables]));
        if (!(strcmp(texto,"="))){
        	validar=true;

        }else if (!(strcmp(texto,"<="))) {
        	validar=true;

        }else if (!(strcmp(texto,">="))){
        	validar=true;

        }else{
        	validar=false;

        	break;
        }

    }
    return validar;

}

void getInterTables(){

	if (gtk_toggle_button_get_active (GTK_TOGGLE_BUTTON(getIntermediateValue))) {
		interTables=1;
		printf("El valor del check %d\n",interTables );
	}else{
		interTables=0;
		printf("El valor del check %d\n",interTables );
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
	if(validarOperadores()){
		free(initialTableFunc);
		validarOperadores();
		getRestricNumber();
		getRestric();
		buildTable();
		getInterTables();
		makeBeamer();
		showBeamer();

	}else{
		GtkWidget* dialog;
                    GtkDialogFlags flags = GTK_DIALOG_DESTROY_WITH_PARENT;
                    dialog = gtk_message_dialog_new (GTK_WINDOW(mainW),flags,GTK_MESSAGE_ERROR,
                                 GTK_BUTTONS_CLOSE,
                                 "Error: Digite un Operador Correcto");
		gtk_dialog_run (GTK_DIALOG (dialog));
		gtk_widget_destroy (dialog);

	}

}



// called when window is closed
void on_window_main_destroy()
{

    gtk_main_quit();
}
