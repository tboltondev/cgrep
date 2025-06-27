#ifndef OUTPUT_HANDLER_H
#define OUTPUT_HANDLER_H

#include "search_result.h"
#include "searcher.h"

void to_stdout(SearchResult sr, ResultHandlerContext rh_ctx);

void json_to_stdout(SearchResult sr, ResultHandlerContext rh_ctx);

void to_file(SearchResult sr, ResultHandlerContext rh_ctx);

void json_to_file(SearchResult sr, ResultHandlerContext rh_ctx);

void csv_to_stdout(SearchResult sr, ResultHandlerContext rh_ctx);

void csv_to_file(SearchResult sr, ResultHandlerContext rh_ctx);

#endif
