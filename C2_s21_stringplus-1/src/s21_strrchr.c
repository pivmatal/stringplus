#include "s21_string.h"

// 17 Выполняет поиск последнего вхождения символа c (беззнаковый тип) в строке,
// на которую указывает аргумент str

char *s21_strrchr(const char *str, int c) {
  char *last_sym = s21_NULL;
  s21_size_t i = 0;
  for (; i < s21_strlen(str) + 1; i++) {
    if (str[i] == c) {
      last_sym = (char *)(str + i);
    }
  }
  return last_sym;
}
