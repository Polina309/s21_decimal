#include "../s21_decimal.h"

s21_big_decimal convert_to_big_decimal(s21_decimal num) {
  s21_big_decimal big_decimal = {0};

  big_decimal.bits[0] = num.bits[0];
  big_decimal.bits[1] = num.bits[1];
  big_decimal.bits[2] = num.bits[2];
  big_decimal.bits[7] = num.bits[3];

  return big_decimal;
}

int convert_from_big_decimal(s21_big_decimal big, s21_decimal *result) {
  int flag = 0;

  if (!result) {
    flag = 1;
  }

  if (flag == 0) {
    result->bits[0] = 0;
    result->bits[1] = 0;
    result->bits[2] = 0;
    result->bits[3] = 0;

    for (int i = 0; i < 96; i++) {
      if (big_get_bit(big, i)) {
        set_bit(result, i, 1);
      }
    }

    for (int i = 96; i < 192; i++) {
      if (big_get_bit(big, i)) {
        flag = 1;
      }
    }
  }

  return flag;
}
