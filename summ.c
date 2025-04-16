#include "../s21_decimal.h"

void summ(s21_big_decimal val1, s21_big_decimal val2, s21_big_decimal *res) {
  int carry = 0;
  for (int i = 0; i < 224; i++) {
    int bit1 = big_get_bit(val1, i);
    int bit2 = big_get_bit(val2, i);
    int sum = bit1 + bit2 + carry;

    big_set_bit(res, i, sum % 2);
    carry = sum / 2;

    if (i >= 96 && carry) {
      return;
    }
  }
}