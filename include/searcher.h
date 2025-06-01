#ifndef SEARCHER_H
#define SEARCHER_H

#include "search_result.h"

typedef void (*ResultHandler)(SearchResult);

void search_file(SearchResult *sr, const char *pattern, const char *path);

void handle_search_file(const char *pattern, const char *path,
                        ResultHandler result_handler);

void search_dir_recursively(const char *pattern, const char *base_path,
                            ResultHandler result_handler, int current_depth,
                            int max_depth); // TODO: exclude .gitignore files / dirs, binaries etc

void search(const char *pattern, const char *path, ResultHandler result_handler);

#endif
