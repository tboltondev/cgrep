#include <string.h>

int count_escape_chars(char *str) {
  int escape_chars_count = 0;
  for (int i = 0; i < strlen(str); i++) {
    switch (str[i]) {
      case '\"':
      case '\\':
        escape_chars_count++;
        break;
    }
  }
  return escape_chars_count;
}

void escape_chars(char *str, char *out_str) {
  int k = 0;
  for (int j = 0; j < strlen(str); j++) {
    switch (str[j]) {
      case '\"': out_str[k++] = '\\'; out_str[k++] = '\"'; break;
      case '\\': out_str[k++] = '\\'; out_str[k++] = '\\'; break;
      default: out_str[k++] = str[j]; break;
    }
  }

  out_str[k] = '\0';
}
