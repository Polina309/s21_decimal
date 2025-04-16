#include "../s21_decimal.h"

void multiply_by_10(s21_big_decimal* value) {
  unsigned long long carry = 0;

  for (int i = 0; i < 7; i++) {
    unsigned long long temp = (unsigned long long)value->bits[i] * 10 + carry;
    value->bits[i] = temp & 0xFFFFFFFF;
    carry = temp >> 32;
  }

  if (carry > 0) {
    if (value->bits[7] + carry > 0xFFFFFFFF) {
      printf("Error: Overflow to multiply to 10!\n");
    } else {
      value->bits[7] += carry;
    }
  }
}

int normalisation(s21_big_decimal* value1, int scale1, s21_big_decimal* value2,
                  int scale2, int* new_scale) {
  int flag = 0;

  if (scale1 == scale2) {
    *new_scale = scale1;
  } else {
    s21_big_decimal* value_to_scale = (scale1 < scale2) ? value1 : value2;
    int shift_amount = abs(scale1 - scale2);
    *new_scale = (scale1 > scale2) ? scale1 : scale2;

    for (int i = 0; i < shift_amount && flag == 0; i++) {
      if (overflow_check_big_decimal(value_to_scale)) {
        flag = 1;
      } else {
        multiply_by_10(value_to_scale);
      }
    }
  }

  return flag;
}