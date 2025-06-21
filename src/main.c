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

  if (args.json)
    result_handler = json_stdout;

  if (args.output_file) {
    rh_ctx.output_filepath = args.output_file;

    if (!truncate_file(rh_ctx.output_filepath)) {
      fprintf(stderr, "Error truncating file: %s\n", rh_ctx.output_filepath);
      return FILE_READ_ERR;
    }

    result_handler = to_file;

    if (args.json)
      // TODO: doesn't write single json obj, writes one object per file that contains matches
      result_handler = json_to_file;
  }

  return search(args.pattern, args.path, result_handler, rh_ctx);
}
