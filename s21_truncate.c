#include "../s21_decimal.h"

int s21_truncate(s21_decimal value, s21_decimal *result) {
  int flag = OK;

  if (result == NULL) {
    flag = CALCULATION_ERROR;
  }
  null_decimal(result);

  *result = value;
  int scale = (value.bits[3] >> 16) & 0xFF;
  if (scale > 0) {
    for (int i = 0; i < scale; i++) {
      divide_by_ten(result);
    }
  }
  set_scale(result, 0);

  return flag;
}
