#include "../s21_decimal.h"

int multiply(s21_big_decimal big_val1, s21_big_decimal big_val2,
             s21_big_decimal *res) {
  for (int i = 0; i < 8; i++) {
    res->bits[i] = 0;
  }

  for (int i = 0; i < 224; i++) {
    if (big_get_bit(big_val2, i)) {
      s21_big_decimal temp = {0};

      for (int j = 0; j < 224; j++) {
        if (big_get_bit(big_val1, j)) {
          big_set_bit(&temp, j + i, 1);
        }
      }

      unsigned long long carry = 0;
      for (int k = 0; k < 8; k++) {
        unsigned long long sum =
            (unsigned long long)res->bits[k] + temp.bits[k] + carry;
        res->bits[k] = sum & 0xFFFFFFFF;
        carry = sum >> 32;
      }
    }
  }
  return 0;
}

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int flag = 0;

  if (result == NULL) {
    flag = 1;
  }

  if (flag == 0) {
    int sign1 = get_sign(value_1);
    int sign2 = get_sign(value_2);
    int scale1 = get_scale(value_1);
    int scale2 = get_scale(value_2);

    s21_big_decimal big_val1 = convert_to_big_decimal(value_1);
    s21_big_decimal big_val2 = convert_to_big_decimal(value_2);

    int new_scale = 0;
    if (normalisation(&big_val1, scale1, &big_val2, scale2, &new_scale) != 0) {
      flag = 1;
    }

    if (flag == 0) {
      s21_big_decimal res = {0};
      if (multiply(big_val1, big_val2, &res) != 0) {
        flag = 1;
      }

      if (flag == 0 && overflow_check_big_decimal(&res)) {
        flag = 1;
      }

      if (flag == 0 && convert_from_big_decimal(res, result) != 0) {
        flag = 1;
      }

      if (flag == 0) {
        set_sign(result, sign1 ^ sign2);
        set_scale(result, scale1 + scale2 > 28 ? 28 : scale1 + scale2);
      }
    }
  }

  return flag;
}