#include "s21_string.h"

// 6 Добавляет строку, на которую указывает src, в конец строки, на которую
// указывает dest

char *s21_strcat(char *dest, const char *src) {
  char *res = dest;
  char *str = (char *)src;
  while (*res != '\0') {
    res++;
  }
  do {
    *res = *str;
    res++;
    str++;
  } while (*str != '\0');
  return dest;
}
