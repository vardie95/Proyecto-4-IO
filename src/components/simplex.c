#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int actual_column = 0;
int actual_row = 0;
double z_value;
bool negs_left;
bool min;
bool unbounded = false;

// Functions declaration -------------------------------------------------------
void simplex(double** table, int rows, int columns, bool min);
void most_negative_column(double* table_row, int columns);
void define_base_row(double** table, int rows, int columns);
void apply_basic_division(double** table, int rows, int columns);
void apply_algebraic_operations(double** table, int rows, int columns);
bool verify_negs(double* table_row, int columns);
void print_table(double** table, int m, int n);

// Functions definition --------------------------------------------------------
void simplex(double** table, int rows, int columns, bool min)
{
  negs_left = verify_negs(table[0], columns);
  print_table(table, rows, columns);
  while (negs_left == true)
  {
    most_negative_column(table[0], columns);
    define_base_row(table, rows, columns);
    if (unbounded == true)
    {
      break;
    }
    apply_basic_division(table, rows, columns);
    apply_algebraic_operations(table, rows, columns);
    negs_left = verify_negs(table[0], columns);
    print_table(table, rows, columns);
  }
  if (unbounded == false)
  {
    if (min == true)
    {
      z_value = -1.0 * table[0][columns - 1];
    } else {
      z_value = table[0][columns - 1];
    }
    printf("Z = %f\n", z_value);
  }
  else
  {
    printf("%s\n", "Unbounded problem...");
  }
}

void most_negative_column(double* table_row, int columns)
{
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

void define_base_row(double** table, int rows, int columns)
{
  actual_row = 0;
  for (int i = 1; i < rows; i++)
  {
    if (table[i][actual_column] > 0)
    {
      if (actual_row == 0)
      {
        actual_row = i;
      }
      else
      {
        double saved_number = table[actual_row][columns - 1] / table[actual_row][actual_column];
        double new_number = table[i][columns - 1] / table[i][actual_column];
        if (new_number < saved_number)
        {
          actual_row = i;
        }
      }
    }
  }
  if (actual_row == 0)
  {
    unbounded = true;
  }
}

void apply_basic_division(double** table, int rows, int columns)
{
  double divider = table[actual_row][actual_column];
  for (int j = 0; j < columns; j++)
  {
    table[actual_row][j] = table[actual_row][j] / divider;
  }
}

void apply_algebraic_operations(double** table, int rows, int columns)
{
  double temp_value;
  for (int i = 0; i < rows; i++)
  {
    if (i != actual_row){
      temp_value = -1.0 * table[i][actual_column];
      printf("i = %d | actual_row = %d\n", i, actual_row);
      for (int j = 0; j < columns; j++)
      {
        table[i][j] = table[i][j] + (temp_value*table[actual_row][j]);
      }
    }
  }
}

bool verify_negs(double* table_row, int columns)
{
  negs_left = false;
  for (int j = 0; j < (columns - 1); j++)
  {
    if (table_row[j] < 0)
    {
      negs_left = true;
      break;
    }
  }
  return negs_left;
}

void print_table(double** table, int m, int n)
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
