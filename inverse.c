#include "../s21_decimal.h"

s21_big_decimal inverse(s21_big_decimal value) {
  s21_big_decimal temp = value;

  if (overflow_check_big_decimal(&temp)) {
    printf("INVERSE: Overflow detected before inversion!\n");
    temp = (s21_big_decimal){0};
  } else {
    for (int i = 0; i < 7; i++) {
      temp.bits[i] = ~temp.bits[i];
    }

    int carry = 1;
    for (int i = 0; i < 7; i++) {
      uint64_t sum = (uint64_t)temp.bits[i] + carry;
      temp.bits[i] = (uint32_t)(sum & 0xFFFFFFFF);
      carry = (sum >> 32) & 1;
    }
  }

  return temp;
}