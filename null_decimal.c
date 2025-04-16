#include "../s21_decimal.h"

void null_decimal(s21_decimal* s21_decimal) {
  s21_decimal->bits[0] = 0;
  s21_decimal->bits[1] = 0;
  s21_decimal->bits[2] = 0;
  s21_decimal->bits[3] = 0;
}