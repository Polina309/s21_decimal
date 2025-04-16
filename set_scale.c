#include "../s21_decimal.h"

int set_scale(s21_decimal* s21_decimal, int scale_value) {
  int flag = 0;

  if (scale_value < 0 || scale_value > 28) {
    flag = 1;
  }

  if (flag == 0) {
    int sign = s21_decimal->bits[3] & (1 << 31);
    s21_decimal->bits[3] = sign | ((scale_value & 0xFF) << 16);
  }

  return flag;
}