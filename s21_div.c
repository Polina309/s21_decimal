#include "../s21_decimal.h"

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int error = 0;

  if (is_zero(&value_2)) {
    error = 3;
  }

  if (!error) {
    s21_scale_to_common(&value_1, &value_2);

    int sign = get_sign(value_1) ^ get_sign(value_2);

    s21_decimal quotient = {0};
    s21_decimal remainder = {0};
    s21_perform_division(value_1, value_2, &quotient, &remainder);

    if (!is_zero(&remainder)) {
      if (s21_bank_round(&quotient, &remainder, value_2)) {
        error = 1;
      }
    }

    if (!error) {
      if (overflow_check(&quotient)) {
        error = sign ? 2 : 1;
      }
    }

    if (!error) {
      set_sign(&quotient, sign);
      *result = quotient;
    }
  }

  return error;
}

void s21_perform_division(s21_decimal dividend, s21_decimal divisor,
                          s21_decimal *quotient, s21_decimal *remainder) {
  uint64_t num_low = ((uint64_t)(uint32_t)dividend.bits[0] |
                      ((uint64_t)(uint32_t)dividend.bits[1] << 32));
  uint64_t num_high = (uint32_t)dividend.bits[2];

  uint64_t denom = ((uint64_t)(uint32_t)divisor.bits[0] |
                    ((uint64_t)(uint32_t)divisor.bits[1] << 32));

  memset(quotient, 0, sizeof(s21_decimal));
  memset(remainder, 0, sizeof(s21_decimal));

  if (num_high == 0 && denom != 0) {
    uint64_t q = num_low / denom;
    uint64_t rem = num_low % denom;

    quotient->bits[0] = (int)(q & 0xFFFFFFFFU);
    quotient->bits[1] = (int)((q >> 32) & 0xFFFFFFFFU);
    remainder->bits[0] = (int)(rem & 0xFFFFFFFFU);
    return;
  }

  uint64_t remainder_high = num_high;
  uint64_t remainder_low = num_low;
  uint64_t q_high = 0, q_low = 0;

  for (int i = 95; i >= 0; i--) {
    uint64_t carry = (remainder_low >> 63) & 1;
    remainder_low = (remainder_low << 1) | ((remainder_high >> 31) & 1);
    remainder_high = (remainder_high << 1) | carry;

    if (remainder_high > denom ||
        (remainder_high == denom && remainder_low >= denom)) {
      remainder_low -= denom;
      if (remainder_low > ~denom) remainder_high--;
      remainder_high -= denom;

      if (i >= 64) {
        q_high |= (1ULL << (i - 64));
      } else {
        q_low |= (1ULL << i);
      }
    }
  }

  quotient->bits[0] = (int)(q_low & 0xFFFFFFFFU);
  quotient->bits[1] = (int)((q_low >> 32) & 0xFFFFFFFFU);
  quotient->bits[2] = (int)q_high;

  remainder->bits[0] = (int)(remainder_low & 0xFFFFFFFFU);
  remainder->bits[1] = (int)((remainder_low >> 32) & 0xFFFFFFFFU);
  remainder->bits[2] = (int)remainder_high;
}

int s21_bank_round(s21_decimal *quotient, s21_decimal *remainder,
                   s21_decimal divisor) {
  uint64_t rem =
      ((uint64_t)remainder->bits[0]) | ((uint64_t)remainder->bits[1] << 32);
  uint64_t div =
      ((uint64_t)divisor.bits[0]) | ((uint64_t)divisor.bits[1] << 32);

  int need_round = 0;

  if (rem * 2 > div) {
    need_round = 1;
  } else if (rem * 2 == div && (quotient->bits[0] & 1)) {
    need_round = 1;
  }

  if (need_round) {
    int carry = 1;
    for (int i = 0; i < 3 && carry; i++) {
      uint64_t sum = (uint64_t)quotient->bits[i] + carry;
      quotient->bits[i] = (uint32_t)(sum & 0xFFFFFFFF);
      carry = (sum >> 32) & 0x1;
    }

    if (carry) {
      return 1;
    }
  }

  return 0;
}