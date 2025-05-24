#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "search_result.h"

#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_RESET   "\x1b[0m"
// TODO: file for colors

SearchResult create_search_result(size_t initial_capacity, char *path) {
  SearchResult sr;
  strcpy(sr.path, path);
  sr.lines = malloc(initial_capacity * sizeof(char *));
  sr.count = 0;
  sr.capacity = initial_capacity;
  return sr;
}

void add_to_search_result(SearchResult *sr, char *line) {
  if (sr->count == sr->capacity) {
    sr->capacity *= 2;
    sr->lines = realloc(sr->lines, sr->capacity * sizeof(char *));
  }
  sr->lines[sr->count] = strdup(line);
  sr->count++;
}

void print_search_result(SearchResult sr) {
  printf(ANSI_COLOR_MAGENTA "%s\n" ANSI_COLOR_RESET, sr.path);

  for (int i = 0; i < sr.count; i++) {    
    printf("%s", sr.lines[i]);
  }
  printf("\n");
}

void free_search_result(SearchResult *sr) {
  for (int i = 0; i < sr->count; i++) {
    free(sr->lines[i]);
  }
  free(sr->lines);
}
