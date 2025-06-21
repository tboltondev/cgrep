#include "../include/output_handler.h"
#include "../include/colors.h"
#include "../include/file_utils.h"
#include "../include/json_utils.h"
#include "../include/search_result.h"
#include <stdio.h>
#include <string.h>

void to_stdout(SearchResult sr, ResultHandlerContext rh_ctx) {
  printf(ANSI_COLOR_MAGENTA "%s\n" ANSI_COLOR_RESET, sr.path);

  for (int i = 0; i < sr.count; i++) {
    MatchedLine matched = sr.lines[i];
    printf(ANSI_COLOR_GREEN "%i:", matched.line_num);
    // print line up to first match
    printf(ANSI_COLOR_RESET "%.*s", matched.match_position, matched.line);
    // print match
    printf(ANSI_COLOR_RED "%.*s", matched.match_len,
           &matched.line[matched.match_position]);
    // print remainder of line
    printf(ANSI_COLOR_RESET "%s",
           &matched.line[matched.match_position + matched.match_len]);
  }
  printf("\n");
}

void json_stdout(SearchResult sr, ResultHandlerContext rh_ctx) {
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
           escaped_str, sr.lines[i].line_num, sr.lines[i].match_position + 1,
           sr.lines[i].match_len);
    if (i != sr.count - 1)
      printf(",");
  }

  printf("]");
  printf("}\n");
}

void to_file(SearchResult sr, ResultHandlerContext rh_ctx) {
  if (rh_ctx.output_filepath == NULL) {
    fprintf(stderr, "Missing output file path\n");
    // return -1;
  }
  FILE *outfile = fopen(rh_ctx.output_filepath, "a");
  if (outfile == NULL) {
    fprintf(stderr, "Error opening file: %s\n", rh_ctx.output_filepath);
    // return -1;
  }

  fprintf(outfile, "%s\n", sr.path);

  for (int i = 0; i < sr.count; ++i) {
    MatchedLine matched_line = sr.lines[i];
    fprintf(outfile, "%i: %s", matched_line.line_num, matched_line.line);
  }

  fprintf(outfile, "\n");

  fclose(outfile);
  // return 0;
}

void json_to_file(SearchResult sr, ResultHandlerContext rh_ctx) {
  if (rh_ctx.output_filepath == NULL) {
    fprintf(stderr, "Missing output file path\n");
    // return -1;
  }
  FILE *outfile = fopen(rh_ctx.output_filepath, "a");
  if (outfile == NULL) {
    fprintf(stderr, "Error opening file: %s\n", rh_ctx.output_filepath);
    // return -1;
  }

  fprintf(outfile, "{\"path\":\"%s\",", sr.path);
  fprintf(outfile, "\"results\":[");

  for (int i = 0; i < sr.count; i++) {
    char *line = sr.lines[i].line;
    remove_newlines(line); // TODO: maybe make copy

    int esc_chars_count = count_escape_chars(line);
    char escaped_str[strlen(line) + esc_chars_count + 1];
    escape_chars(line, escaped_str);

    fprintf(outfile, "{"
           "\"line\":\"%s\","
           "\"line_number\":%d,"
           "\"match_position\":%d,"
           "\"match_length\":%d"
           "}",
           escaped_str, sr.lines[i].line_num,
           sr.lines[i].match_position + 1,
           sr.lines[i].match_len);
    if (i != sr.count - 1)
      fprintf(outfile, ",");
  }

  fprintf(outfile, "]");
  fprintf(outfile, "}\n");
}
