#ifndef SEARCH_RESULT_H
#define SEARCH_RESULT_H

#include <stddef.h>

typedef struct {
  char **lines;
  size_t count;
  size_t capacity;
} SearchResult;

SearchResult create_search_result(size_t initial_capacity);

void add_to_search_result(SearchResult *sr, char *line);

void print_search_result(SearchResult *sr);

void free_search_result(SearchResult *sr);

#endif
