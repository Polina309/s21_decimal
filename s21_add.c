#include "../s21_decimal.h"

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int flag = 0;
  s21_big_decimal res = {0};
  int result_sign = 0;
  int new_scale = 0;

  if (result == NULL) {
    flag = 1;
  }

  if (flag == 0) {
    int sign1 = get_sign(value_1);
    int sign2 = get_sign(value_2);

    set_sign(&value_1, 0);
    set_sign(&value_2, 0);

    int scale1 = get_scale(value_1);
    int scale2 = get_scale(value_2);

    s21_big_decimal big_val1 = convert_to_big_decimal(value_1);
    s21_big_decimal big_val2 = convert_to_big_decimal(value_2);

    if (normalisation(&big_val1, scale1, &big_val2, scale2, &new_scale) != 0) {
      flag = 1;
    }

    if (flag == 0) {
      if (sign1 == sign2) {
        summ(big_val1, big_val2, &res);
        result_sign = sign1;
      } else {
        if (big_is_less(big_val1, big_val2)) {
          s21_big_decimal temp_inverse = inverse(big_val1);
          if (overflow_check_big_decimal(&temp_inverse)) {
            flag = 1;
          } else {
            summ(big_val2, temp_inverse, &res);
            result_sign = sign2;
          }
        } else {
          s21_big_decimal temp_inverse = inverse(big_val2);
          if (overflow_check_big_decimal(&temp_inverse)) {
            flag = 1;
          } else {
            summ(big_val1, temp_inverse, &res);
            result_sign = sign1;
          }
        }
      }
    }
  }

  if (flag == 0 && overflow_check_big_decimal(&res)) {
    flag = 1;
  }

  if (flag == 0 && convert_from_big_decimal(res, result) != 0) {
    flag = 1;
  }

  if (flag == 0) {
    set_scale(result, new_scale);
    set_sign(result, result_sign);
  }

  return flag;
}