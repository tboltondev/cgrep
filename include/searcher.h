#ifndef SEARCHER_H
#define SEARCHER_H

#include "search_result.h"
#include "search_status.h"

typedef struct {
  const char *output_filepath;
} ResultHandlerContext;

typedef void (*ResultHandler)(SearchResult, ResultHandlerContext);

SearchStatus search(const char *pattern, const char *path,
                    ResultHandler result_handler, ResultHandlerContext rh_ctx);

#endif
