#include "../include/arg_parser.h"
#include "../include/output_handler.h" // TODO: find out why absolute includes are not working
#include "../include/searcher.h"
#include <stdio.h>

int main(int argc, char *argv[]) {
  Args args = {0};
  if (!parse_args(argc, argv, &args))
    return 1;

  ResultHandler result_handler = to_stdout;
  ResultHandlerContext rh_ctx = {0};

  if (args.json)
    result_handler = json_stdout;

  if (args.output_file) {
    rh_ctx.output_filepath = args.output_file;

    // TODO: avoid file writes spreading across multiple files
    // open file in write mode to clear contents if already exists
    FILE *fp = fopen(rh_ctx.output_filepath, "w");
    if (fp == NULL) {
      fprintf(stderr, "Error opening file: %s\n", rh_ctx.output_filepath);
      // return -1;
    }
    fclose(fp);

    result_handler = to_file;

    if (args.json)
      // TODO: doesn't produce valid json file
      result_handler = json_to_file;
  }

  return search(args.pattern, args.path, result_handler, rh_ctx);
}
