#ifndef SEARCHER_H
#define SEARCHER_H

#include "output_handler.h"
#include "exit_status.h"

ExitStatus search(const char *pattern, const char *path, OutputHandler output_handler);

#endif
