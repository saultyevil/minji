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

#define merror(msg, ...){ \
  printf("(%s:%i): ", (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__), __LINE__); \
  mlog(msg, ##__VA_ARGS__); \
}

#endif //MINJI_LOG_H
