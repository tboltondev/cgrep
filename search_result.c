#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "search_result.h"

SearchResult create_search_result(size_t initial_capacity) {
  SearchResult search_result;
  search_result.lines = malloc(initial_capacity * sizeof(char *));
  search_result.count = 0;
  search_result.capacity = initial_capacity;
  return search_result;
}

void add_to_search_result(SearchResult *sr, char *line) {
  if (sr->count == sr->capacity) {
    sr->capacity *= 2;
    sr->lines = realloc(sr->lines, sr->capacity * sizeof(char *));
  }
  sr->lines[sr->count] = strdup(line);
  sr->count++;
}

void print_search_result(SearchResult *sr) {
  for (int i = 0; i < sr->count; i++) {    
    printf("%s", sr->lines[i]);
  }
}

void free_search_result(SearchResult *sr) {
  for (int i = 0; i < sr->count; i++) {
    free(sr->lines[i]);
  }
  free(sr->lines);
}

// int main() {
//   SearchResult sr = create_search_result(4);

//   add_to_search_result(&sr, "abc");
//   add_to_search_result(&sr, "def");

//   print_search_result(&sr);

//   free_search_result(&sr);
// }
