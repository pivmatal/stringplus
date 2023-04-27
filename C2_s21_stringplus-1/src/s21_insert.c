#include "s21_string.h"

// Возвращает новую строку, в которой указанная строка (str) вставлена в
// указанную позицию (start_index) в данной строке (src). В случае какой-либо
// ошибки следует вернуть значение NULL
void *s21_insert(const char *src, const char *str, size_t start_index) {
  char *temp_str = s21_NULL;
  if (src != s21_NULL && str != s21_NULL) {
    s21_size_t len_src = s21_strlen(src);
    s21_size_t len_str = s21_strlen(str);
    s21_size_t new_str = len_src + len_str;

    if (len_str >= start_index) {
      temp_str = (char *)malloc(sizeof(char) * new_str + 1);
    }

    if (temp_str != s21_NULL) {
      for (s21_size_t i = 0, j = 0, x = 0; i < new_str; i++) {
        if (i >= start_index && j < len_src) {
          temp_str[i] = src[i];
          j++;
        } else {
          temp_str[i] = str[x];
          x++;
        }
      }
      temp_str[new_str] = '\0';
    }
  }
  return temp_str;
}
