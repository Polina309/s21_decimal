#include "../s21_decimal.h"

void big_set_bit(s21_big_decimal *value, int bit, unsigned set) {
  int index = bit / 32;
  int offset = bit % 32;
  if (set) {
    value->bits[index] |= (1 << offset);
  } else {
    value->bits[index] &= ~(1 << offset);
  }
}