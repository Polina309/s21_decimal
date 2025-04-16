#include "../s21_decimal.h"

int s21_round(s21_decimal value, s21_decimal *result) {
  int flag = 0;
  if (result == NULL) {
    flag = 1;
  } else {
    null_decimal(result);

    s21_truncate(value, result);

    s21_decimal fraction = {0};
    s21_decimal null_dec = {0};
    s21_decimal unit = {{1, 0, 0, 0}};
    s21_decimal half = {{5, 0, 0, 0x10000}};
    int sign = get_sign(value);

    s21_sub(value, *result, &fraction);
    set_sign(&fraction, 0);
    set_sign(result, 0);

    if (s21_is_not_equal(fraction, null_dec)) {
      if (s21_is_greater(fraction, half)) {
        s21_add(*result, unit, result);
      } else if (s21_is_equal(fraction, half)) {
        if (((int)result->bits[0] & 1) == 1) {
          s21_add(*result, unit, result);
        }
      }
    }
    set_sign(result, sign);
  }

  return flag;
}