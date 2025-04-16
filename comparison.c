#include "../s21_decimal.h"

void s21_scale_to_common(s21_decimal *a, s21_decimal *b) {
  int scale_a = (a->bits[3] >> 16) & 0xFF;
  int scale_b = (b->bits[3] >> 16) & 0xFF;
  int max_scale = (scale_a > scale_b) ? scale_a : scale_b;

  s21_scale_to_power_of_ten(a, max_scale);
  s21_scale_to_power_of_ten(b, max_scale);
}

void s21_scale_to_power_of_ten(s21_decimal *decimal, int max_scale) {
  int current_scale = (decimal->bits[3] >> 16) & 0xFF;
  bool need_multiply = false;
  bool need_divide = false;

  if (max_scale != current_scale) {
    if (max_scale > current_scale) {
      need_multiply = true;
    } else {
      need_divide = true;
    }
  }

  if (need_multiply || need_divide) {
    int diff = abs(max_scale - current_scale);

    for (int i = 0; i < diff; ++i) {
      if (need_multiply) {
        multiply_by_ten(decimal);
      } else {
        divide_by_ten(decimal);
      }
    }

    decimal->bits[3] &= 0xFF00FFFF;
    decimal->bits[3] |= (max_scale << 16);
  }
}

void multiply_by_ten(s21_decimal *decimal) {
  uint32_t carry = 0;
  for (int i = 0; i < 3; ++i) {
    uint64_t temp = (uint64_t)decimal->bits[i] * 10 + carry;
    decimal->bits[i] = temp & 0xFFFFFFFF;
    carry = temp >> 32;
  }
  if (carry) {
    decimal->bits[3] += carry;
  }
}

void divide_by_ten(s21_decimal *decimal) {
  uint32_t remainder = 0;
  for (int i = 2; i >= 0; --i) {
    uint64_t temp = (uint64_t)decimal->bits[i] + ((uint64_t)remainder << 32);
    decimal->bits[i] = temp / 10;
    remainder = temp % 10;
  }
}

int s21_is_less(s21_decimal a, s21_decimal b) {
  bool is_less = false;
  bool a_sign = (a.bits[3] & 0x80000000) != 0;
  bool b_sign = (b.bits[3] & 0x80000000) != 0;

  if (a_sign != b_sign) {
    is_less = a_sign && !b_sign;
  } else {
    s21_scale_to_common(&a, &b);

    bool is_different = false;

    for (int i = 2; i >= 0 && !is_different; i--) {
      if (a.bits[i] != b.bits[i]) {
        if (a_sign) {
          is_less = (a.bits[i] > b.bits[i]);
        } else {
          is_less = (a.bits[i] < b.bits[i]);
        }
        is_different = true;
      }
    }
  }

  return is_less ? 1 : 0;
}

int s21_is_equal(s21_decimal a, s21_decimal b) {
  s21_scale_to_common(&a, &b);

  bool is_equal = true;

  if ((a.bits[3] & 0x80000000) != (b.bits[3] & 0x80000000)) {
    is_equal = false;
  } else {
    for (int i = 0; i < 3 && is_equal; i++) {
      if (a.bits[i] != b.bits[i]) {
        is_equal = false;
      }
    }
  }

  return is_equal ? 1 : 0;
}

int s21_is_less_or_equal(s21_decimal a, s21_decimal b) {
  return s21_is_less(a, b) || s21_is_equal(a, b);
}

int s21_is_not_equal(s21_decimal a, s21_decimal b) {
  return !s21_is_equal(a, b);
}

int s21_is_greater_or_equal(s21_decimal a, s21_decimal b) {
  return !s21_is_less(a, b);
}

int s21_is_greater(s21_decimal a, s21_decimal b) {
  bool is_greater = false;
  bool a_sign = (a.bits[3] >> 31) & 1;
  bool b_sign = (b.bits[3] >> 31) & 1;

  if (a_sign != b_sign) {
    is_greater = !a_sign && b_sign;
  } else {
    s21_scale_to_common(&a, &b);

    for (int i = 2; i >= 0 && !is_greater; i--) {
      if (a.bits[i] != b.bits[i]) {
        if (a_sign) {
          is_greater = (a.bits[i] < b.bits[i]);
        } else {
          is_greater = (a.bits[i] > b.bits[i]);
        }
      }
    }
  }

  return is_greater ? 1 : 0;
}
