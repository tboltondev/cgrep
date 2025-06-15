#include "../include/search_result.h"
#include "../include/colors.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

MatchedLine create_matched_line(char *line, size_t match_start, size_t match_end,
                                int line_num) {
  int line_len = strlen(line) + 1;

  MatchedLine matched_line = {.line = malloc(line_len),
                              .line_num = line_num,
                              .line_len = line_len,
                              .match_position = match_start,
                              .match_len = match_end - match_start};

  strncpy(matched_line.line, line, matched_line.line_len);

  return matched_line;
}

void free_matched_line(MatchedLine *matched_line) { free(matched_line->line); }

SearchResult create_search_result(size_t initial_capacity, const char *path) {
  SearchResult search_result = {
      .lines = malloc(initial_capacity * sizeof(MatchedLine)),
      .count = 0,
      .capacity = initial_capacity};

  strncpy(search_result.path, path, strlen(path));

  return search_result;
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
    MatchedLine matched = sr.lines[i];
    printf(ANSI_COLOR_GREEN "%i:", matched.line_num);
    printf(ANSI_COLOR_RESET "%.*s", matched.match_position,
           matched.line); // print line up to first match
    printf(ANSI_COLOR_RED "%.*s", matched.match_len,
           &matched.line[matched.match_position]); // print match
    printf(ANSI_COLOR_RESET "%s",
           &matched.line[matched.match_position +
                         matched.match_len]); // print remainder of line
  }
  printf("\n");
}

void free_search_result(SearchResult *sr) {
  for (int i = 0; i < sr->count; i++) {
    free_matched_line(&sr->lines[i]);
  }
  free(sr->lines);
}
