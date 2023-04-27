#include "s21_string.h"

// 9 Сравнивает строку, на которую указывает str1, со строкой, на которую
// указывает str2

int s21_strcmp(const char *str1, const char *str2) {
  int res = 0;
  for (; res == 0 && (*str1 != '\0' || *str2 != '\0'); str1++, str2++)
    res = (int)*str1 - (int)*str2;

  return res;
}
