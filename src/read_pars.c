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

void
find_par_file (char *file_path)
{
  int ierr;

  Log ("Please input the file path to the parameter file: ");
  ierr = scanf ("%s", file_path);
  if (ierr == EOF)
    Exit (INVALID_INPUT_ERROR, "Nothing entered for parameter file file path\n");
}

void
init_parameter_file (char *file_path)
{
  PAR_FILE_PTR = fopen (file_path, "r");
  if (!PAR_FILE_PTR)
    Exit (FILE_OPEN_ERROR, "Could not find parameter file '%s'\n", file_path);
  Log (" - Loaded parameter file '%s'\n", file_path);
}

void
input_double (char *par_name, double *value)
{
  int ierr;
  char input_value[LINE_LEN];

  Log ("%s not found, input value:\n%s (%f): ", par_name, par_name, *value);
  ierr = scanf ("%s", input_value);
  if (ierr == EOF)
    Exit (INVALID_INPUT_ERROR, "Nothing entered for input par\n");
  *value = atof (input_value);
}

void
input_int (char *par_name, int *value)
{
  int ierr;
  char input_value[LINE_LEN];

  Log ("%s not found, input value:\n%s (%i): ", par_name, par_name, *value);
  ierr = scanf ("%s", input_value);
  if (ierr == EOF)
    Exit (INVALID_INPUT_ERROR, "Nothing entered for input par\n");
  *value = atoi (input_value);
}

void
input_string (char *par_name, char *value)
{
  int ierr;
  char input_value[LINE_LEN];

  Log ("%s not found, input value: \n%s (%s): ", par_name, par_name, value);
  ierr = scanf ("%s", input_value);
  if (ierr == EOF)
    Exit (INVALID_INPUT_ERROR, "Nothing entered for input par\n");
  strcpy (value, input_value);
}

void
get_double (char *par_name, double *value)
{
  int line_num, found_par;
  char line[LINE_LEN], ini_par_name[LINE_LEN], par_sep[LINE_LEN], par_value[LINE_LEN];

  /*
   * Iterate through the lines in the file and attempt to find a match between
   * the first column labels, ini_par_name, and the parameter name hoping
   * to be set a value, par_name.
   */

  rewind (PAR_FILE_PTR);

  line_num = 0;
  found_par = FALSE;
  while (fgets (line, LINE_LEN, PAR_FILE_PTR) != NULL)
  {
    line_num++;
    if (line[0] == '#' || line[0] == '\r' || line[0] == '\n')
      continue;
    if (sscanf (line, "%s %s %s", ini_par_name, par_sep, par_value) != 3)
      Exit (PAR_FILE_SYNTAX_ERROR, "Syntax error on line %i in parameter file\n", line_num);
    if (strcmp (par_name, ini_par_name) == 0)
    {
      *value = atof (par_value);
      found_par = TRUE;
    }
  }

  if (!found_par)
    input_double (par_name, value);
}

void
get_int (char *par_name, int *value)
{
  int line_num, found_par;
  char line[LINE_LEN], ini_par_name[LINE_LEN], par_sep[LINE_LEN], par_value[LINE_LEN];

  /*
   * Iterate through the lines in the file and attempt to find a match between
   * the first column labels, ini_par_name, and the parameter name hoping
   * to be set a value, par_name.
   */

  rewind (PAR_FILE_PTR);

  line_num = 0;
  found_par = FALSE;
  while (fgets (line, LINE_LEN, PAR_FILE_PTR) != NULL)
  {
    line_num++;
    if (line[0] == '#' || line[0] == '\r' || line[0] == '\n')
      continue;
    if (sscanf (line, "%s %s %s", ini_par_name, par_sep, par_value) != 3)
      Exit (PAR_FILE_SYNTAX_ERROR, "Syntax error on line %i in parameter file\n", line_num);
    if (strcmp (par_name, ini_par_name) == 0)
    {
      *value = atoi (par_value);
      found_par = TRUE;
    }
  }

  if (!found_par)
    input_int (par_name, value);
}

void
get_string (char *par_name, char *value)
{
  int line_num, found_par;
  char line[LINE_LEN], ini_par_name[LINE_LEN], par_sep[LINE_LEN], par_value[LINE_LEN];

  /*
   * Iterate through the lines in the file and attempt to find a match between
   * the first column labels, ini_par_name, and the parameter name hoping
   * to be set a value, par_name.
   */

  rewind (PAR_FILE_PTR);

  line_num = 0;
  found_par = FALSE;
  while (fgets (line, LINE_LEN, PAR_FILE_PTR) != NULL)
  {
    line_num++;
    if (line[0] == '#' || line[0] == '\r' || line[0] == '\n')
      continue;
    if (sscanf (line, "%s %s %s", ini_par_name, par_sep, par_value) != 3)
      Exit (PAR_FILE_SYNTAX_ERROR, "Syntax error on line %i in parameter file\n", line_num);
    if (strcmp (par_name, ini_par_name) == 0)
    {
      strcpy (value, par_value);
      found_par = TRUE;
    }
  }

  if (!found_par)
    input_string (par_name, value);
}

void
get_optional_int (char *par_name, int *value)
{
  int line_num;
  char line[LINE_LEN], ini_par_name[LINE_LEN], par_sep[LINE_LEN], par_value[LINE_LEN];

  /*
   * Iterate through the lines in the file and attempt to find a match between
   * the first column labels, ini_par_name, and the parameter name hoping
   * to be set a value, par_name.
   */

  rewind (PAR_FILE_PTR);

  line_num = 0;
  while (fgets (line, LINE_LEN, PAR_FILE_PTR) != NULL)
  {
    line_num++;
    if (line[0] == '#' || line[0] == '\r' || line[0] == '\n')
      continue;
    if (sscanf (line, "%s %s %s", ini_par_name, par_sep, par_value) != 3)
      Exit (PAR_FILE_SYNTAX_ERROR, "Syntax error on line %i in parameter file\n", line_num);
    if (strcmp (par_name, ini_par_name) == 0)
      *value = atoi (par_value);
  }
}

void
get_optional_double (char *par_name, double *value)
{
  int line_num;
  char line[LINE_LEN], ini_par_name[LINE_LEN], par_sep[LINE_LEN], par_value[LINE_LEN];

  /*
   * Iterate through the lines in the file and attempt to find a match between
   * the first column labels, ini_par_name, and the parameter name hoping
   * to be set a value, par_name.
   */

  rewind (PAR_FILE_PTR);

  line_num = 0;
  while (fgets (line, LINE_LEN, PAR_FILE_PTR) != NULL)
  {
    line_num++;
    if (line[0] == '#' || line[0] == '\r' || line[0] == '\n')
      continue;
    if (sscanf (line, "%s %s %s", ini_par_name, par_sep, par_value) != 3)
      Exit (PAR_FILE_SYNTAX_ERROR, "Syntax error on line %i in parameter file\n", line_num);
    if (strcmp (par_name, ini_par_name) == 0)
      *value = atof (par_value);
  }
}
