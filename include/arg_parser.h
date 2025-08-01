#ifndef ARG_PARSER_H
#define ARG_PARSER_H

typedef enum {
  OUT_TXT,
  OUT_JSON,
  OUT_CSV
} OutFormat;

typedef struct {
  const char *pattern;
  const char *path;
  const char *out_file;
  OutFormat out_format;
} Args;

int parse_args(int argc, char *argv[], Args *args);

#endif
