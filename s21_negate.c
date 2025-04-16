#include "../s21_decimal.h"

int s21_negate(s21_decimal value, s21_decimal *result) {
  int flag = OK;

  if (result == NULL) {
    flag = CALCULATION_ERROR;
  } else
    null_decimal(result);

  for (int i = 0; i < 4; i++) {
    result->bits[i] = value.bits[i];
  }

  if (value.bits[0] == 0 && value.bits[1] == 0 && value.bits[2] == 0 &&
      value.bits[3] == 0) {
    result->bits[3] = 0;
    return flag;
  }

  if (get_sign(value)) {
    set_sign(result, 0);
  } else
    set_sign(result, 1);

  return flag;
}