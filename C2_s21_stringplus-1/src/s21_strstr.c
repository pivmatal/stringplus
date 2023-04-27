#include "s21_string.h"

// 19 Находит первое вхождение всей строки needle (не включая завершающий
// нулевой символ), которая появляется в строке haystack

char *s21_strstr(const char *haystack, const char *needle) {
  char *h = (char *)haystack;
  char *first_sym = s21_NULL;
  int size = s21_strlen(needle);
  int flag = 1;
  while (*h != '\0' && flag == 1) {
    if (s21_strncmp(h, needle, size) == 0) {
      flag = 0;
      first_sym = h;
    } else {
      h++;
    }
  }
  return first_sym;
}
