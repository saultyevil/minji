/* ***************************************************************************
 *
 * @file
 *
 * @author
 *
 * @brief
 *
 * @details
 *
 * ************************************************************************** */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "minji.h"

FILE *PAR_FILE_PTR;

int find_par_file (char *file_path)
{
  int ierr;
  
  Log ("Please input the file path to the parameter file: ");
  ierr = scanf ("%s", file_path);
  if (ierr == EOF)
    Exit (5, "find_par_file: Nothing entered for parameter file file path\n");
  
  return SUCCESS;
}

int init_parameter_file (char *file_path)
{
  PAR_FILE_PTR = fopen (file_path, "r");
  if (!PAR_FILE_PTR)
    Exit (2, "init_parameter_file: Could not find parameter file '%s'\n",
          file_path);
  Log (" - Loaded parameter file '%s'\n", file_path);
  
  return SUCCESS;
}

int get_double (char *par_name, double *value)
{
  int line_num = 0;
  int found_par = FALSE;
  char line[LINE_LEN], ini_par_name[LINE_LEN], par_sep[LINE_LEN],
    par_value[LINE_LEN];
  
  /*
   * Iterate through the lines in the file and attempt to find a match between
   * the first column labels, ini_par_name, and the parameter name hoping
   * to be set a value, par_name.
   */
  
  rewind (PAR_FILE_PTR);
  
  while (fgets (line, LINE_LEN, PAR_FILE_PTR) != NULL)
  {
    line_num++;
    if (line[0] == '#' || line[0] == '\r' || line[0] == '\n')
      continue;
    if (sscanf (line, "%s %s %s", ini_par_name, par_sep, par_value) != 3)
      Exit (7, "get_double: Syntax error on line %i in parameter file\n",
            line_num);
    if (strcmp (par_name, ini_par_name) == 0)
    {
      *value = atof (par_value);
      found_par = TRUE;
    }
  }
  
  if (!found_par)
    input_double (par_name, value);
  else
    Log_verbose ("%s %f\n", par_name, *value);
  
  return SUCCESS;
}

int get_int (char *par_name, int *value)
{
  int line_num = 0;
  int found_par = FALSE;
  char line[LINE_LEN], ini_par_name[LINE_LEN], par_sep[LINE_LEN],
    par_value[LINE_LEN];
  
  /*
   * Iterate through the lines in the file and attempt to find a match between
   * the first column labels, ini_par_name, and the parameter name hoping
   * to be set a value, par_name.
   */
  
  rewind (PAR_FILE_PTR);
  
  while (fgets (line, LINE_LEN, PAR_FILE_PTR) != NULL)
  {
    line_num++;
    if (line[0] == '#' || line[0] == '\r' || line[0] == '\n')
      continue;
    if (sscanf (line, "%s %s %s", ini_par_name, par_sep, par_value) != 3)
      Exit (7, "get_double: Syntax error on line %i in parameter file\n",
            line_num);
    if (strcmp (par_name, ini_par_name) == 0)
    {
      *value = atoi (par_value);
      found_par = TRUE;
    }
  }
  
  if (!found_par)
    input_int (par_name, value);
  else
    Log_verbose ("%s %i\n", par_name, *value);
  
  return SUCCESS;
}

int get_string  (char *par_name, char *value)
{
  int line_num = 0;
  int found_par = FALSE;
  char line[LINE_LEN], ini_par_name[LINE_LEN], par_sep[LINE_LEN],
    par_value[LINE_LEN];
  
  /*
   * Iterate through the lines in the file and attempt to find a match between
   * the first column labels, ini_par_name, and the parameter name hoping
   * to be set a value, par_name.
   */
  
  rewind (PAR_FILE_PTR);
  
  while (fgets (line, LINE_LEN, PAR_FILE_PTR) != NULL)
  {
    line_num++;
    if (line[0] == '#' || line[0] == '\r' || line[0] == '\n')
      continue;
    if (sscanf (line, "%s %s %s", ini_par_name, par_sep, par_value) != 3)
      Exit (7, "get_double: Syntax error on line %i in parameter file\n",
            line_num);
    if (strcmp (par_name, ini_par_name) == 0)
    {
      strcpy (value, par_value);
      found_par = TRUE;
    }
  }
  
  if (!found_par)
    input_string (par_name, value);
  else
    Log_verbose ("%s %i\n", par_name, *value);
  
  return SUCCESS;
}


int input_double (char *par_name, double *value)
{
  int ierr;
  char input_value[LINE_LEN];
  
  Log ("%s not found, input value:\n%s (%f): ", par_name, par_name, *value);
  ierr = scanf ("%s", input_value);
  if (ierr == EOF)
    Exit (9, "input_double: Nothing entered for input par\n");
  *value = atof (input_value);
  
  return SUCCESS;
}

int input_int (char *par_name, int *value)
{
  int ierr;
  char input_value[LINE_LEN];
  
  Log ("%s not found, input value:\n%s (%i): ", par_name, par_name, *value);
  ierr = scanf ("%s", input_value);
  if (ierr == EOF)
    Exit (9, "input_int: Nothing entered for input par\n");
  *value = atoi (input_value);
  
  return SUCCESS;
}

int input_string (char *par_name, char *value)
{
  int ierr;
  char input_value[LINE_LEN];
  
  Log ("%s not found, input value: \n%s (%s): ", par_name, par_name, value);
  ierr = scanf ("%s", input_value);
  if (ierr == EOF)
    Exit (9, "input_string: Nothing entered for input par\n");
  strcpy (value, input_value);
  
  return SUCCESS;
}

int get_optional_int (char *par_name, int *value)
{
  int line_num = 0;
  char line[LINE_LEN], ini_par_name[LINE_LEN], par_sep[LINE_LEN],
    par_value[LINE_LEN];

  /*
   * Iterate through the lines in the file and attempt to find a match between
   * the first column labels, ini_par_name, and the parameter name hoping
   * to be set a value, par_name.
   */

  rewind (PAR_FILE_PTR);

  while (fgets (line, LINE_LEN, PAR_FILE_PTR) != NULL)
  {
    line_num++;
    if (line[0] == '#' || line[0] == '\r' || line[0] == '\n')
      continue;
    if (sscanf (line, "%s %s %s", ini_par_name, par_sep, par_value) != 3)
      Exit (7, "get_double: Syntax error on line %i in parameter file\n",
            line_num);
    if (strcmp (par_name, ini_par_name) == 0)
      *value = atoi (par_value);
  }

  return SUCCESS;
}

int get_optional_double (char *par_name, double *value)
{
  int line_num = 0;
  char line[LINE_LEN], ini_par_name[LINE_LEN], par_sep[LINE_LEN],
    par_value[LINE_LEN];

  /*
   * Iterate through the lines in the file and attempt to find a match between
   * the first column labels, ini_par_name, and the parameter name hoping
   * to be set a value, par_name.
   */

  rewind (PAR_FILE_PTR);

  while (fgets (line, LINE_LEN, PAR_FILE_PTR) != NULL)
  {
    line_num++;
    if (line[0] == '#' || line[0] == '\r' || line[0] == '\n')
      continue;
    if (sscanf (line, "%s %s %s", ini_par_name, par_sep, par_value) != 3)
      Exit (7, "get_double: Syntax error on line %i in parameter file\n",
            line_num);
    if (strcmp (par_name, ini_par_name) == 0)
      *value = atof (par_value);
  }

  return SUCCESS;
}
