/* ************************************************************************** */
/**
* @file    log.h
* @author  Edward Parkinson
* @brief   Contains various constants and macros for logging.
*
* @details
*
* *************************************************************************** */

#ifndef MINJI_LOG_H
#define MINJI_LOG_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "fmt.h"

#define merror(msg, ...){ \
  printf("%s(%i): ", (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__), __LINE__); \
  mlog(msg, ##__VA_ARGS__); \
}

#define mabort(errnum, msg, ...){ \
  printf("\n%s\n", FMT_SEPARATOR); \
  printf("%s(%i): ", (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__), __LINE__); \
  exit_program(errnum, msg, ##__VA_ARGS__);\
  exit(errnum);\
}

#endif //MINJI_LOG_H
