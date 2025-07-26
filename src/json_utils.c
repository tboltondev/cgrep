#include <string.h>

int json_count_escape_chars(const char *str) {
  int escape_chars_count = 0;
  for (int i = 0; i < strlen(str); ++i) {
    switch (str[i]) {
    case '\"':
    case '\\':
      escape_chars_count++;
      break;
    default: ;
    }
  }
  return escape_chars_count;
}

void json_str_escape(const char *str, char *out_str) {
  int k = 0;
  for (int j = 0; j < strlen(str); ++j) {
    switch (str[j]) {
    case '\"':
      out_str[k++] = '\\';
      out_str[k++] = '\"';
      break;
    case '\\':
      out_str[k++] = '\\';
      out_str[k++] = '\\';
      break;
    default:
      out_str[k++] = str[j];
      break;
    }
  }

  out_str[k] = '\0';
}
