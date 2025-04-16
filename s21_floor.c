#include "../s21_decimal.h"

int s21_floor(s21_decimal value, s21_decimal *result) {
  int flag = 0;
  if (result == NULL) {
    flag = 1;
  } else {
    null_decimal(result);

    s21_truncate(value, result);

    s21_decimal fraction = {0};
    s21_decimal null_dec = {0};
    s21_decimal unit = {{1, 0, 0, 0}};
    int sign = get_sign(*result);

    s21_sub(value, *result, &fraction);
    set_sign(&fraction, 0);

    if (sign && s21_is_not_equal(fraction, null_dec)) {
      s21_sub(*result, unit, result);
    }
  }

  return flag;
}