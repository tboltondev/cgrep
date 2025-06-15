#ifndef RESULT_STATUS_H
#define RESULT_STATUS_H

typedef enum {
    SEARCH_SUCCESS = 0,
    INVALID_FILE_PATH_ERR, // TODO: currently not used
    FILE_READ_ERR,
    MAX_DIR_DEPTH_ERR,
    REGEX_COMPILATION_ERR
} SearchStatus;

#endif
