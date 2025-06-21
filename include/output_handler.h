#ifndef OUTPUT_HANDLER_H
#define OUTPUT_HANDLER_H

#include "search_result.h"
#include "searcher.h"

int to_stdout(SearchResult sr, ResultHandlerContext rh_ctx);

int json_stdout(SearchResult sr, ResultHandlerContext rh_ctx);

int to_file(SearchResult sr, ResultHandlerContext rh_ctx);

int json_to_file(SearchResult sr, ResultHandlerContext rh_ctx);

#endif
