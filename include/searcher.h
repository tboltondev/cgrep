#ifndef SEARCHER_H
#define SEARCHER_H

#include "search_result.h"
#include "search_status.h"

typedef struct {
  const char *output_filepath;
  void (*handler)(SearchResult, const char*);
} ResultHandler;

SearchStatus search(const char *pattern, const char *path, ResultHandler result_handler);

#endif
