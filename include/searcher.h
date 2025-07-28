#ifndef SEARCHER_H
#define SEARCHER_H

#include "output_handler.h"
#include "search_status.h"

SearchStatus search(const char *pattern, const char *path, OutputHandler output_handler);

#endif
