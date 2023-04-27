#include "s21_string.h"

// 12 Копирует до n символов из строки, на которую указывает src, в dest.
char *s21_strncpy(char *dest, const char *src, s21_size_t n) {
  if (n != 0) {
    register char *d = dest;
    register const char *s = src;
    do {
      if ((*d++ = *s++) == 0) {
        while (--n != 0) *d++ = 0;
        break;
      }
    } while (--n != 0);
  }
  return dest;
}
