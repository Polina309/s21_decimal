#include "../s21_decimal.h"

int big_is_less(s21_big_decimal value_1, s21_big_decimal value_2) {
  int result = 0;
  int found = 0;

  for (int i = 223; i >= 0 && !found; i--) {
    int bit1 = big_get_bit(value_1, i);
    int bit2 = big_get_bit(value_2, i);

    if (bit1 != bit2) {
      result = bit1 < bit2;
      found = 1;
    }
  }

  return result;
}