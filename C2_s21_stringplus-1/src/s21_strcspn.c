#include "s21_string.h"

// 13 Вычисляет длину начального сегмента строки str1,
// полностью состоящего из символов, не входящих в строку str2.
s21_size_t s21_strcspn(const char *str1, const char *str2) {
  s21_size_t res = 0;
  register const char *p, *imposter;
  register char c, sc;
  for (p = str1;;) {
    c = *p++;
    imposter = str2;
    do {
      if ((sc = *imposter++) == c) return (p - 1 - str1);
    } while (sc != 0);
  }
  return res;
}
