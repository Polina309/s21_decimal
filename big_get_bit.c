#include "../s21_decimal.h"

unsigned big_get_bit(s21_big_decimal value, int bit) {
  int index = bit / 32;
  int offset = bit % 32;
  return (value.bits[index] >> offset) & 1;
}