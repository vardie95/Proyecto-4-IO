#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int actual_row;
int actual_column;

// Functions declaration -------------------------------------------------------
void prepare_m_table(double** table, int rows, int columns);
void most_negative_column_M(double* table_row, int columns);
void apply_algebraic_operations_M(double** table, int rows, int columns);
void print_table_M(double** table, int rows, int columns);


// Functions definition --------------------------------------------------------
void prepare_m_table(double** table, int rows, int columns)
{
  for (int j = 0; j < columns - 1; j++)
  {
    if (table[0][j] != 0)
    {
      actual_column = j;
      for (int i = 1; i < rows; i++)
      {
        if (table[i][j] == 1)
        {
          actual_row = i;
          break;
        }
      }
      apply_algebraic_operations_M(table, rows, columns);
      print_table_M(table, rows, columns);
    }
  }
}

void most_negative_column_M(double* table_row, int columns)
{
  bool draw = false;
  double temp_value = 0;
  for (int j = 0; j < (columns - 1); j++)
  {
    if (table_row[j] < 0)
    {
      if (table_row[j] < table_row[actual_column])
      {
        actual_column = j;
      }
    }
  }
}

void apply_algebraic_operations_M(double** table, int rows, int columns)
{
  double temp_value;
  for (int i = 0; i < rows; i++)
  {
    if (i != actual_row){
      temp_value = -1.0 * table[i][actual_column];
      for (int j = 0; j < columns; j++)
      {
        table[i][j] = table[i][j] + (temp_value*table[actual_row][j]);
      }
    }
  }
}

void print_table_M(double** table, int m, int n)
{
  for (int i=0; i<m; i++)
	{
	    for(int j=0; j<n; j++)
	    {
	    	printf("%f     ", table[i][j]);
	    }
	    printf("\n");
	}
	printf("\n");
}
