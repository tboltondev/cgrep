#include "arg_parser.h"
#include "file_utils.h"
#include "output_handler.h"
#include "searcher.h"
#include <stdio.h>

int main(int argc, char *argv[]) {
  Args args = {0};
  if (!parse_args(argc, argv, &args))
    return ARG_PARSE_ERR;

  ResultHandler result_handler = to_stdout;
  ResultHandlerContext rh_ctx = {0};

  if (args.output_file) {
    rh_ctx.output_filepath = args.output_file;
    result_handler = to_file;

    if (!truncate_file(rh_ctx.output_filepath)) {
      fprintf(stderr, "Error truncating file: %s\n", rh_ctx.output_filepath);
      return FILE_READ_ERR;
    }

    if (args.json) {
      result_handler = json_to_file;
    }

    if (args.csv) {
      // TODO: shouldn't be in main
      FILE *outfile = fopen(rh_ctx.output_filepath, "w");
      if (outfile == NULL)
        fprintf(stderr, "Error opening file: %s\n", rh_ctx.output_filepath);

      // this makes truncate unnecessary
      fprintf(outfile, "file path, line number, line, match position, match length\n");
      fclose(outfile);

      result_handler = csv_to_file;
    }
  } else if (args.json) {
    result_handler = json_to_stdout;
  } else if (args.csv) {
    // TODO: this shouldn't be in main
    fprintf(stdout, "filepath, line number, line, match position, match length\n");
    result_handler = csv_to_stdout;
  }

   return search(args.pattern, args.path, result_handler, rh_ctx);
}
