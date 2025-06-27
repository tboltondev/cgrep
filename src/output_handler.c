#include "output_handler.h"
#include "colors.h"
#include "csv_utils.h"
#include "file_utils.h"
#include "json_utils.h"
#include "search_result.h"
#include "searcher.h"
#include <stddef.h>
#include <stdio.h>
#include <string.h>

void to_stdout(SearchResult sr, ResultHandlerContext rh_ctx) {
  printf(ANSI_COLOR_MAGENTA "%s\n" ANSI_COLOR_RESET, sr.path);

  for (int i = 0; i < sr.count; ++i) {
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

void json_to_stdout(SearchResult sr, ResultHandlerContext rh_ctx) {
  printf("{\"path\":\"%s\",", sr.path);
  printf("\"results\":[");

  for (int i = 0; i < sr.count; ++i) {
    const MatchedLine ml = sr.lines[i];
    remove_newline_chars(ml.line);

    int esc_chars_count = json_count_escape_chars(ml.line);
    char escaped_str[strlen(ml.line) + esc_chars_count + 1];
    json_str_escape(ml.line, escaped_str);

    printf("{"
           "\"line\":\"%s\","
           "\"line_number\":%d,"
           "\"match_position\":%d,"
           "\"match_length\":%d"
           "}",
           escaped_str, ml.line_num, ml.match_position + 1,
           ml.match_len);
    if (i != sr.count - 1)
      printf(",");
  }

  printf("]");
  printf("}\n");
}

void to_file(SearchResult sr, ResultHandlerContext rh_ctx) {
  if (rh_ctx.output_filepath == NULL)
    fprintf(stderr, "Missing output file path\n");

  FILE *outfile = fopen(rh_ctx.output_filepath, "a");
  if (outfile == NULL)
    fprintf(stderr, "Error opening file: %s\n", rh_ctx.output_filepath);

  fprintf(outfile, "%s\n", sr.path);

  for (int i = 0; i < sr.count; ++i) {
    MatchedLine matched_line = sr.lines[i];
    fprintf(outfile, "%i: %s", matched_line.line_num, matched_line.line);
  }

  fprintf(outfile, "\n");

  fclose(outfile);
}

void json_to_file(SearchResult sr, ResultHandlerContext rh_ctx) {
  if (rh_ctx.output_filepath == NULL)
    fprintf(stderr, "Missing output file path\n");

  FILE *outfile = fopen(rh_ctx.output_filepath, "a");
  if (outfile == NULL)
    fprintf(stderr, "Error opening file: %s\n", rh_ctx.output_filepath);

  fprintf(outfile, "{\"path\":\"%s\",", sr.path);
  fprintf(outfile, "\"results\":[");

  for (int i = 0; i < sr.count; ++i) {
    char *line = sr.lines[i].line;
    remove_newline_chars(line);

    int esc_chars_count = json_count_escape_chars(line);
    char escaped_str[strlen(line) + esc_chars_count + 1];
    json_str_escape(line, escaped_str);

    fprintf(outfile,
            "{"
            "\"line\":\"%s\","
            "\"line_number\":%d,"
            "\"match_position\":%d,"
            "\"match_length\":%d"
            "}",
            escaped_str, sr.lines[i].line_num, sr.lines[i].match_position + 1,
            sr.lines[i].match_len);
    if (i != sr.count - 1)
      fprintf(outfile, ",");
  }

  fprintf(outfile, "]");
  fprintf(outfile, "}\n");
}

void csv_to_stdout(SearchResult sr, ResultHandlerContext rh_ctx) {
  for (int i = 0; i < sr.count; ++i) {
    const MatchedLine ml = sr.lines[i];
    remove_newline_chars(ml.line);

    // could do this only if csv_count_escape_chars > 0
    size_t num_quotes = csv_count_quotes(ml.line);
    char escaped_str[strlen(ml.line) + num_quotes + 1];
    csv_str_escape(ml.line, escaped_str);

    if (needs_quotes(escaped_str)) {
      const size_t esc_len = strlen(escaped_str);
      const size_t qs_len = esc_len + 3;
      char quoted_str[qs_len];

      // TODO: maybe move into utils
      quoted_str[0] = '\"';
      strlcpy(quoted_str + 1, escaped_str, sizeof(quoted_str) + 1);
      quoted_str[qs_len - 2] = '\"';
      quoted_str[qs_len - 1] = '\0';

      printf("%s, %i, %s, %i, %i\n", sr.path, ml.line_num, quoted_str,
             ml.match_position, ml.match_len);
    } else {
    printf("%s, %i, %s, %i, %i\n", sr.path, ml.line_num, escaped_str,
           ml.match_position, ml.match_len);
    }
  }
}

void csv_to_file(SearchResult sr, const ResultHandlerContext rh_ctx) {
  if (rh_ctx.output_filepath == NULL)
    fprintf(stderr, "Missing output file path\n");

  FILE *outfile = fopen(rh_ctx.output_filepath, "a");
  if (outfile == NULL)
    fprintf(stderr, "Error opening file: %s\n", rh_ctx.output_filepath);

  for (int i = 0; i < sr.count; ++i) {
    const MatchedLine ml = sr.lines[i];

    remove_newline_chars(ml.line);

    // could do this only if csv_count_escape_chars > 0
    size_t num_quotes = csv_count_quotes(ml.line);
    char escaped_str[strlen(ml.line) + num_quotes + 1];
    csv_str_escape(ml.line, escaped_str);

    if (needs_quotes(escaped_str)) {
      const size_t esc_len = strlen(escaped_str);
      const size_t qs_len = esc_len + 3;
      char quoted_str[qs_len];

      // TODO: maybe move into utils
      quoted_str[0] = '\"';
      strlcpy(quoted_str + 1, escaped_str, sizeof(quoted_str) + 1);
      quoted_str[qs_len - 2] = '\"';
      quoted_str[qs_len - 1] = '\0';

      fprintf(outfile, "%s, %i, %s, %i, %i\n", sr.path, ml.line_num, quoted_str,
             ml.match_position, ml.match_len);
    } else {
    fprintf(outfile, "%s, %i, %s, %i, %i\n", sr.path, ml.line_num, escaped_str,
           ml.match_position, ml.match_len);
    }
  }
}
