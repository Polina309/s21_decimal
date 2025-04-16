#include "../s21_decimal.h"

void set_bit(s21_decimal* s21_decimal, int bit, unsigned value) {
  int block = bit / 32;
  int position = bit % 32;
  if (value) {
    s21_decimal->bits[block] |= (1 << position);
  } else {
    s21_decimal->bits[block] &= ~(1 << position);
  }
}
