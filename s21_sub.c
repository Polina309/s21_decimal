#include "../s21_decimal.h"

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int flag = 0;

  if (result == NULL) {
    flag = 1;
  }

  if (flag == 0) {
    if ((value_1.bits[3] & 0x80000000) != (value_2.bits[3] & 0x80000000)) {
      value_2.bits[3] ^= 0x80000000;
      flag = s21_add(value_1, value_2, result);
    } else {
      s21_decimal temp = value_2;
      temp.bits[3] ^= 0x80000000;
      flag = s21_add(value_1, temp, result);
    }

    if (flag == 0) {
      s21_decimal min_decimal = {
          {0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
      if (s21_is_less(*result, min_decimal)) {
        flag = 1;
      }
    }
  }

  return flag;
}