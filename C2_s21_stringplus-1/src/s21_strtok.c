#include "s21_string.h"

// 20 Разбивает строку str на ряд токенов, разделенных delim

char *s21_strtok(char *str, const char *delim) {
  static char *res = s21_NULL;
  if (str) {
    res = str;
    while (*res && s21_strchr(delim, *res)) *res++ = '\0';
  }
  if (res != s21_NULL) {
    if (*res != '\0') {
      str = res;
      while (*res && !s21_strchr(delim, *res)) res++;
      while (*res && s21_strchr(delim, *res)) *res++ = '\0';
    } else {
      str = s21_NULL;
    }
  } else {
    str = s21_NULL;
  }
  return str;
}
