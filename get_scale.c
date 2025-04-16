#include "../s21_decimal.h"

int get_scale(s21_decimal s21_decimal) {
  return (s21_decimal.bits[3] >> 16) & 0xFF;
}
