#include "arg_parser.h"
#include "file_utils.h"
#include "output_handler.h"
#include "searcher.h"
#include <stdio.h>

int main(const int argc, char *argv[]) {
  Args args = {0};
  if (!parse_args(argc, argv, &args))
    return ARG_PARSE_ERR;

  ResultHandler rh = { .handler = to_stdout };

  if (args.out_file) {
    rh.handler = to_file;
    rh.output_filepath = args.out_file;

    if (!truncate_file(rh.output_filepath)) {
      fprintf(stderr, "Error truncating file: %s\n", rh.output_filepath);
      return FILE_READ_ERR;
    }

    if (args.out_format == OUT_JSON)
      rh.handler = json_to_file;

    if (args.out_format == OUT_CSV) {
      // TODO: shouldn't be in main
      FILE *outfile = fopen(rh.output_filepath, "w");
      if (outfile == NULL)
        fprintf(stderr, "Error opening file: %s\n", rh.output_filepath);

      // this makes truncate unnecessary
      fprintf(outfile, "file path, line number, line, match position, match length\n");
      fclose(outfile);

      rh.handler = csv_to_file;
    }
  } else if (args.out_format == OUT_JSON) {
    rh.handler = json_to_stdout;
  } else if (args.out_format == OUT_CSV) {
    // TODO: this shouldn't be in main
    fprintf(stdout, "filepath, line number, line, match position, match length\n");
    rh.handler = csv_to_stdout;
  }

   return search(args.pattern, args.path, rh);
}
