#ifndef RESULT_STATUS_H
#define RESULT_STATUS_H

typedef enum {
    SEARCH_SUCCESS = 0,
    FILE_READ_ERR,
    MAX_DIR_DEPTH_ERR,
    REGEX_COMPILATION_ERR,
    ARG_PARSE_ERR,
    MEM_ALLOC_ERR,
} SearchStatus;

#endif
