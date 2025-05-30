#include "../include/search_result.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_RESET "\x1b[0m"
// TODO: file for colors

MatchedLine create_matched_line(char *line, char *match, int line_num) {
  MatchedLine matched_line;
  matched_line.line = malloc(strlen(line) + 1);
  strcpy(matched_line.line, line);
  matched_line.line_num = line_num;
  matched_line.line_len = strlen(line);
  matched_line.match_position = match - line;
  matched_line.match_len = strlen(match);
  return matched_line;
}

void free_matched_line(MatchedLine *matched_line) {
  free(matched_line->line);
}

SearchResult create_search_result(size_t initial_capacity, char *path) {
  SearchResult sr;
  strcpy(sr.path, path);
  sr.lines = malloc(initial_capacity * sizeof(MatchedLine));
  sr.count = 0;
  sr.capacity = initial_capacity;
  return sr;
}

void add_to_search_result(SearchResult *sr, MatchedLine line) {
  if (sr->count == sr->capacity) {
    sr->capacity *= 2;
    sr->lines = realloc(sr->lines, sr->capacity * sizeof(MatchedLine));
  }
  sr->lines[sr->count] = line;
  sr->count++;
}

void print_search_result(SearchResult sr) {
  printf(ANSI_COLOR_MAGENTA "%s\n" ANSI_COLOR_RESET, sr.path);

  for (int i = 0; i < sr.count; i++) {
    printf("%s", sr.lines[i].line);
  }
  printf("\n");
}

void free_search_result(SearchResult *sr) {
  for (int i = 0; i < sr->count; i++) {
    free_matched_line(&sr->lines[i]);
  }
  free(sr->lines);
}
