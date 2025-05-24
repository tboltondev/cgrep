#include <stdio.h>
#include <string.h>
#include "searcher.h"
#include "search_result.h"

#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_RESET   "\x1b[0m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define MAX_LINE_SIZE 300 * sizeof(char)

void search_file(SearchResult *sr, char *pattern, char *path) {
  FILE *file = fopen(path, "r");
  if (file == NULL) {
    printf("Error opening file %s\n", path); // TODO: return error codes
  }

  char line[300]; // Max chars in line, maybe make dynamic

  int line_num = 1;

  while (fgets(line, sizeof(line), file) != NULL) {
    char *match = strstr(line, pattern);

    if (match != NULL) {
      int matched_position = match - line;
      int match_length = strlen(pattern);
      int line_len = strlen(line);

      char matched_line[MAX_LINE_SIZE];
      int buffer_size = sizeof(matched_line);
      int offset = 0;

      offset +=
          snprintf(matched_line + offset, buffer_size - offset, ANSI_COLOR_GREEN);
      offset +=
          snprintf(matched_line + offset, buffer_size - offset, "%i:", line_num);
      offset +=
          snprintf(matched_line + offset, buffer_size - offset, ANSI_COLOR_RESET);
      offset +=
          snprintf(matched_line + offset, buffer_size - offset, "%.*s",
                   matched_position, line); // part of line before first match
      offset +=
          snprintf(matched_line + offset, buffer_size - offset, ANSI_COLOR_RED);
      offset += snprintf(matched_line + offset, buffer_size - offset, "%.*s",
                         match_length, &line[matched_position]); // first match
      offset +=
          snprintf(matched_line + offset, buffer_size - offset, ANSI_COLOR_RESET);
      offset +=
          snprintf(matched_line + offset, buffer_size - offset, "%s",
                   &line[matched_position + match_length]); // remainder of line

      add_to_search_result(sr, matched_line);
    }
    line_num++;
  }
}

// int main() {
//   SearchResult sr = create_search_result(10);
//   search_file(&sr, "hello", "./test");
//   print_search_result(&sr);
// }
