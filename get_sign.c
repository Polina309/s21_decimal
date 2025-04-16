#include "../s21_decimal.h"

int get_sign(s21_decimal s21_decimal) {
  return (s21_decimal.bits[3] >> 31) & 1;
}
