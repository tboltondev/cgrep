#include "../include/output_handler.h"
#include "../include/search_result.h"
#include "../include/file_utils.h"
#include "../include/json_utils.h"
#include <stdio.h>
#include <string.h>

void to_stdout(SearchResult sr) { print_search_result(sr); }

void json_stdout(SearchResult sr) {
  printf("{\"path\":\"%s\",", sr.path);
  printf("\"results\":[");

  for (int i = 0; i < sr.count; i++) {
    char *line = sr.lines[i].line;
    remove_newlines(line); // TODO: maybe make copy

    int esc_chars_count = count_escape_chars(line);
    char escaped_str[strlen(line) + esc_chars_count + 1];
    escape_chars(line, escaped_str);

    printf("{"
        "\"line\":\"%s\","
        "\"line_number\":%d,"
        "\"match_position\":%d,"
        "\"match_length\":%d"
        "}",
        escaped_str,
        sr.lines[i].line_num,
        sr.lines[i].match_position + 1, // + 1 to because of 0-indexing
        sr.lines[i].match_len
    );
    if (i != sr.count - 1)
      printf(",");
  }

  printf("]");
  printf("}\n");
}
