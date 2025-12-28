#ifndef LOGGER_H
#define LOGGER_H

#include <stdarg.h>

// Logs an action with a timestamp, e.g.:
//   [2025-08-06 12:34:56] Created file 'new.txt'
void log_action(const char *fmt, ...);

#endif