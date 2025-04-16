#include "../s21_decimal.h"

int overflow_check(s21_decimal* value) {
  int error = 0;

  if ((unsigned int)value->bits[2] != 0 || (unsigned int)value->bits[1] != 0 ||
      (unsigned int)value->bits[0] > 0x7FFFFFFFU) {
    int is_negative = (value->bits[3] >> 31) & 1;
    error = is_negative ? 2 : 1;
  }

  if (!error) {
    int scale = (value->bits[3] >> 16) & 0xFF;
    if (scale > 28) {
      error = 1;
    }
  }

  if (!error) {
    if ((unsigned int)value->bits[0] == 0x7FFFFFFFU &&
        (unsigned int)value->bits[1] == 0xFFFFFFFFU &&
        (unsigned int)value->bits[2] == 0xFFFFFFFFU) {
      error = 1;
    }
  }

  return error;
}

int overflow_check_big_decimal(s21_big_decimal* decimal) {
  int critical_overflow = 0;
  int low_bits_set = 0;

  for (int i = 0; i < 96; i++) {
    if (big_get_bit(*decimal, i)) {
      low_bits_set = 1;
    }
  }

  for (int i = 128; i < 224; i++) {
    if (big_get_bit(*decimal, i)) {
      critical_overflow = 1;
    }
  }

  if (low_bits_set && critical_overflow) {
    critical_overflow = 0;
  }

  return critical_overflow;
}