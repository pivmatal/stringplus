#include "s21_string.h"

// 7 Добавляет строку, на которую указывает src, в конец строки, на которую
// указывает dest, длиной до n символов

char *s21_strncat(char *dest, const char *src, s21_size_t n) {
  char *res = dest;
  int count = 0;
  char *str = (char *)src;
  while (*res != '\0') {
    res++;
  }
  do {
    *res = *str;
    res++;
    str++;
    count++;
  } while (*str != '\0' && count < (int)n);
  return dest;
}
