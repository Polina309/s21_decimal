#include "../s21_decimal.h"

void set_sign(s21_decimal* s21_decimal, int set_value) {
  if (set_value) {
    s21_decimal->bits[3] |= (1 << 31);
  } else {
    s21_decimal->bits[3] &= ~(1 << 31);
  }
}