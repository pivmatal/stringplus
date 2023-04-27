#include "s21_string.h"

// 14 Ищет во внутреннем массиве номер ошибки errnum
// и возвращает указатель на строку сообщения об ошибке.
// Вам нужно объявить макросы, содержащие массивы сообщений
// об ошибках для операционных систем Mac и Linux.
// Описания ошибок доступны в оригинальной библиотеке.
// Проверка текущей ОС осуществляется с помощью директив.

char *s21_strerror(int errnum) {
  char *res = s21_NULL;
  static char s21_error_msg[4096] = {"\0"};
  if (errnum < 0 || errnum >= S21_ERRLIST_SIZE) {
    s21_sprintf(s21_error_msg, "%s %d", UNK_ERR, errnum);
    res = s21_error_msg;
  } else {
    res = (char *)s21_sys_errlist[errnum];
  }
  return res;
}
