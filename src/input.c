/* ************************************************************************** */
/**
* @file    input.c
* @author  Edward Parkinson
* @brief   Contains the functions for initializing the simulation grid.
*
* @details
*
* *************************************************************************** */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include "minji.h"

static FILE *pffp;

/* ************************************************************************** */
/**
* @brief
*
* @details
*
* *************************************************************************** */

extern void
query_for_parameter_file(char *filename)
{
  printf("Please input the file path to the parameter file: ");
  const int err = scanf("%s", filename);
  if(!err)
    mabort(FAILURE, "Nothing entered for parameter file");
}

/* ************************************************************************** */
/**
* @brief
*
* @details
*
* *************************************************************************** */

extern void
open_parameter_file(char *filename)
{
  pffp = fopen(filename, "r");

  if(!pffp)
    mabort(FAILURE, "Could not find parameter file: %s", filename);

  mlog("Loaded parameter file '%s'\n", filename);
}

/* ************************************************************************** */
/**
* @brief
*
* @details
*
* *************************************************************************** */

void
close_parameter_file(void)
{
  if(fclose(pffp))
    mlog("Could not close paramater file");  // TODO this should be an error
}

/* ************************************************************************** */
/**
* @brief
*
* @details
*
* *************************************************************************** */

extern void
read_double(char *parameter, double *value)
{
  char line[LINELENGTH];
  char name[LINELENGTH];
  char xvalue[LINELENGTH];

  rewind(pffp);
  int line_num = 0;
  bool found = false;

  while(fgets(line, LINELENGTH, pffp) != NULL)
  {
    line_num++;
    if(line[0] == '#' || line[0] == '\r' || line[0] == '\n')
      continue;

    if(sscanf(line, "%s %s", name, xvalue) != 2)
      mabort(FAILURE, "Syntax error on line %i in parameter file", line_num);

    if(strcmp(parameter, name) == 0)
    {
      *value = strtod(xvalue, NULL);
      found = true;
    }
  }

  if(found == false)
    mabort(FAILURE, "Unable to find parameter %s", parameter);
}

/* ************************************************************************** */
/**
* @brief
*
* @details
*
* *************************************************************************** */

extern void
read_integer(char *parameter, int *value)
{
  char line[LINELENGTH];
  char name[LINELENGTH];
  char xvalue[LINELENGTH];

  rewind(pffp);
  int line_num = 0;
  bool found_par = false;

  while(fgets(line, LINELENGTH, pffp) != NULL)
  {
    line_num++;
    if(line[0] == '#' || line[0] == '\r' || line[0] == '\n')
      continue;

    if(sscanf(line, "%s %s", name, xvalue) != 2)
      mabort(FAILURE, "Syntax error on line %i in parameter file", line_num);

    if(strcmp(parameter, name) == 0)
    {
      *value = (int) strtol(xvalue, NULL, 10);
      found_par = true;
    }
  }

  if(!found_par)
    mabort(FAILURE, "Unable to find parameter %s", parameter);
}

/* ************************************************************************** */
/**
* @brief
*
* @details
*
* *************************************************************************** */

extern void
get_string(char *parameter, char *value)
{
  char line[LINELENGTH];
  char name[LINELENGTH];
  char xvalue[LINELENGTH];

  rewind(pffp);
  int line_num = 0;
  bool found_par = false;

  while(fgets(line, LINELENGTH, pffp) != NULL)
  {
    line_num++;
    if(line[0] == '#' || line[0] == '\r' || line[0] == '\n')
      continue;

    if(sscanf(line, "%s %s", name, xvalue) != 2)
      mabort(FAILURE, "Syntax error on line %i in parameter file", line_num);

    if(strcmp(parameter, name) == 0)
    {
      strcpy (value, xvalue);
      found_par = true;
    }
  }

  if(!found_par)
    mabort(FAILURE, "Unable to find parameter %s", parameter);
}
