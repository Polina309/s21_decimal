#include <float.h>
#include <math.h>

#include "s21_decimal.h"

int s21_from_int_to_decimal(int src, s21_decimal *dst) {
  if (dst == NULL) return 1;

  null_decimal(dst);

  if (src < 0) {
    set_sign(dst, 1);
    src = -src;
  }
  dst->bits[0] = (unsigned int)src;
  return 0;
}

int s21_from_float_to_decimal(float src, s21_decimal *dst) {
  if (!dst) return 1;

  null_decimal(dst);

  if (isnan(src) || isinf(src) || fabsf(src) < 1e-28f) {
    return 1;
  }

  bool negative = src < 0;
  if (negative) src = -src;

  float scaled = roundf(src * 1000.0f);
  uint32_t int_val = (uint32_t)scaled;

  dst->bits[0] = int_val;
  dst->bits[1] = 0;
  dst->bits[2] = 0;
  set_scale(dst, 3);

  if (negative) {
    set_sign(dst, 1);
  }

  return 0;
}

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
  if (dst == NULL) return 1;

  int sign = get_sign(src);

  int result = src.bits[0];
  result = (sign == 1) ? -result : result;

  *dst = result;
  return 0;
}

int s21_from_decimal_to_float(s21_decimal src, float *dst) {
  if (!dst) return 1;

  __uint128_t value = (__uint128_t)src.bits[0] |
                      ((__uint128_t)src.bits[1] << 32) |
                      ((__uint128_t)src.bits[2] << 64);

  int scale = get_scale(src);
  int sign = get_sign(src);

  *dst = (float)value / powf(10, scale);
  if (sign) *dst = -*dst;

  return 0;
}