#include "s21_string.h"

// 16 Находит первый символ в строке str1, который соответствует любому символу,
// указанному в str2

char *s21_strpbrk(const char *str1, const char *str2) {
  char *res = s21_NULL;
  char *s1 = (char *)str1;
  char *s2 = (char *)str2;
  int size = s21_strlen(str2);
  int flag = 1;

  while (*s1 != '\0' && flag == 1) {
    for (int i = 0; size > i && flag == 1; i++) {
      if (*s1 == s2[i]) {
        flag = 0;
        res = s1;
      }
    }
    s1++;
  }
  return res;
}
