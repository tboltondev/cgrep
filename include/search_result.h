#ifndef SEARCH_RESULT_H
#define SEARCH_RESULT_H

#include <stddef.h>
#include <sys/syslimits.h>

typedef struct {
  char path[PATH_MAX];
  char **lines;
  size_t count;
  size_t capacity;
} SearchResult;

SearchResult create_search_result(size_t initial_capacity, char *path);

void add_to_search_result(SearchResult *sr, char *line);

void print_search_result(SearchResult sr);

void free_search_result(SearchResult *sr);

#endif
