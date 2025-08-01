#include "arg_parser.h"
#include <stdio.h>
#include <string.h>

int parse_args(const int argc, char *argv[], Args *args) {
  if (argc < 2) {
    fprintf(stderr, "Usage: cgrep <pattern> [path] [options]\n");
    return 0;
  }

  args->pattern = argv[1];
  args->path = ".";
  args->out_format = OUT_TXT;

  int arg_index = 2;

  if (arg_index < argc && argv[arg_index][0] != '-')
    args->path = argv[arg_index++];

  for (; arg_index < argc; ++arg_index) {
    if (strcmp(argv[arg_index], "--json") == 0) {
      args->out_format = OUT_JSON;
    } else if (strcmp(argv[arg_index], "--csv") == 0) {
      args->out_format = OUT_CSV;
    } else if (strncmp(argv[arg_index], "-o=", 3) == 0) {
      args->out_file = argv[arg_index] + 3;
    } else {
      fprintf(stderr, "Unknown option: %s\n", argv[arg_index]);
      return 0;
    }
  }

  return 1;
}
