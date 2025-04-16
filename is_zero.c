#include "../s21_decimal.h"

int is_zero(s21_decimal *s21_decimal) {
  int mean = 0;
  if (s21_decimal->bits[0] == 0 && s21_decimal->bits[1] == 0 &&
      s21_decimal->bits[2] == 0)
    mean = 1;
  else
    mean = 0;
  return mean;
}
