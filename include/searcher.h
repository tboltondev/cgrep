#ifndef SEARCHER_H
#define SEARCHER_H

#include "search_result.h"

typedef void (*ResultHandler)(SearchResult);

void search_file(SearchResult *sr, char *pattern, char *path);

void handle_search_file(char *pattern, char *path,
                        ResultHandler result_handler);

void search_dir_recursively(char *pattern, char *base_path,
                            ResultHandler result_handler, int current_depth,
                            int max_depth); // TODO: exclude .gitignore files / dirs, binaries etc

void search(char *pattern, char *path, ResultHandler result_handler);

#endif
