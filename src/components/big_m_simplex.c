#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int actual_row;
int actual_column;
bool negs_left;
int num_variables;
double z_value;
bool showSteps;
bool min;
bool unbounded;
bool multiple_solutions;

// Functions declaration -------------------------------------------------------
void prepare_m_table(double** table, int rows, int columns);
void apply_algebraic_operations_M(double** table, int rows, int columns);
void print_table_M(double** table, int rows, int columns);
void m_simplex(double** table, int rows, int columns, bool min, bool show, int limit);
bool verify_negs_m(double** table_row, int columns, int limit);
void define_base_row_M(double** table, int rows, int columns);
void apply_basic_division_M(double** table, int rows, int columns);
void verify_multiple_solutions_M(double** table, int rows, int columns, int limit);


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

void m_simplex(double** table, int rows, int columns, bool min, bool show, int limit)
{
  negs_left = verify_negs_m(table, columns, limit);
  while (negs_left == true)
  {
    print_table_M(table, rows, columns);
    define_base_row_M(table, rows, columns);
    if (unbounded == true)
    {
      break;
    }
    apply_basic_division_M(table, rows, columns);
    apply_algebraic_operations_M(table, rows, columns);
    negs_left = verify_negs_m(table, columns, limit);
    print_table_M(table, rows, columns);
  }
  if (unbounded == false)
  {
    verify_multiple_solutions_M(table, rows, columns, limit);
    if (multiple_solutions == false) {
      if (min == true)
      {
        z_value = -1.0 * table[1][columns - 1];
      }
      else
      {
        z_value = table[1][columns - 1];
      }
      printf("Z = %f\n", z_value);
    }
    else
    {
      printf("%s\n", "Multiple solutions...");
      get_multiple_solutions(table, rows, columns);
    }
  }
  else
  {
    printf("%s\n", "Unbounded problem...");
  }
}

bool verify_negs_m(double** table, int columns, int limit)
{
  int temp_j = 0;
  double m_j = 0;
  double n_j = 0;
  for (int j = 1; j < limit; j++)
  {
    if (table[0][j] < m_j)
    {
      temp_j = j;
      m_j = table[0][j];
      n_j = table[1][j];
    } else if (m_j == table[0][j]) {
      if (table[1][j] < n_j) {
        temp_j = j;
        n_j = table[1][j];
      }
    }
  }
  actual_column = temp_j;
  if (temp_j == 0) {
    return false;
  }
  else {
    return true;
  }
}

void define_base_row_M(double** table, int rows, int columns)
{
  actual_row = 0;
  for (int i = 2; i < rows; i++)
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

void apply_basic_division_M(double** table, int rows, int columns)
{
  double divider = table[actual_row][actual_column];
  for (int j = 0; j < columns; j++)
  {
    table[actual_row][j] = table[actual_row][j] / divider;
  }
}

void verify_multiple_solutions_M(double** table, int rows, int columns, int limit)
{
  bool found_one;
  for (int j = 1; j < limit; j++)
  {
    found_one = false;
    if (table[0][j] == 0 && table[1][j] == 0)
    {
      for (int i = 2; i < rows; i++)
      {
        if (found_one == false) {
          if (table[i][j] == 1) {found_one = true;}
          else if (table[i][j] != 0){
            multiple_solutions = true;
            actual_column = j;
            break;
          }
        }
        else if (table[i][j] != 0)
        {
          multiple_solutions = true;
          actual_column = j;
          break;
        }
      }
      if (multiple_solutions == true)
      {
        break;
      }
    }
  }
}
