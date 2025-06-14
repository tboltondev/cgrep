#ifndef ARG_PARSER_H
#define ARG_PARSER_H

typedef struct {
  const char *pattern;
  const char *path;
  const char *output_file;
  int json;
} Args;

int parse_args(int argc, char *argv[], Args *args);

#endif
