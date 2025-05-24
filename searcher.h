#ifndef SEARCHER_H
#define SEARCHER_H

#include "search_result.h"

void search_file(SearchResult *sr, char *pattern, char *path);

void search_dir_recursively(char *pattern, char *base_path, int current_depth, int max_depth); // TODO: exclude files / dirs

void search(char *pattern, char *path);

#endif
