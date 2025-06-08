#ifndef SEARCHER_H
#define SEARCHER_H

#include "search_result.h"
#include "search_status.h"

typedef void (*ResultHandler)(SearchResult);

void search_file(SearchResult *sr, const char *pattern, const char *path);

SearchStatus handle_search_file(const char *pattern, const char *path,
                        ResultHandler result_handler);

SearchStatus search_dir_recursively(
    const char *pattern, const char *base_path, ResultHandler result_handler,
    int current_depth,
    int max_depth); // TODO: exclude .gitignore files / dirs, binaries etc

SearchStatus search(const char *pattern, const char *path,
            ResultHandler result_handler);

#endif
