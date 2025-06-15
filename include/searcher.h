#ifndef SEARCHER_H
#define SEARCHER_H

#include "search_result.h"
#include "search_status.h"

typedef void (*ResultHandler)(SearchResult);

SearchStatus search(const char *pattern, const char *path,
            ResultHandler result_handler);

#endif
