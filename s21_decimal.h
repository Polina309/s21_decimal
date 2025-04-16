#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#ifndef S21_DECIMAL

#define OK 0
#define CALCULATION_ERROR 1

typedef struct s21_decimal{
    unsigned int bits[4];
}s21_decimal;

typedef struct s21_big_decimal {
    unsigned int bits[8];
} s21_big_decimal;

#define MAX_BITS 128
#define MAX_BITS_IN_CELL 32
#define MAX_BITS_TO_OVERFLOW 96


// BASE
int is_zero (s21_decimal *s21_decimal);
int big_is_less(s21_big_decimal value_1, s21_big_decimal value_2);
void null_decimal (s21_decimal* s21_decimal);
int get_sign(s21_decimal s21_decimal);
void set_sign(s21_decimal* s21_decimal, int set_value);
int get_scale(s21_decimal s21_decimal);
int set_scale(s21_decimal* s21_decimal, int scale_value);
void set_bit(s21_decimal* s21_decimal, int bit, unsigned value);
s21_big_decimal convert_to_big_decimal(s21_decimal num);
int convert_from_big_decimal(s21_big_decimal big, s21_decimal *result);
unsigned big_get_bit(s21_big_decimal s21_big_decimal, int bit);
void big_set_bit(s21_big_decimal* s21_big_decimal, int bit, unsigned value);
s21_big_decimal inverse(s21_big_decimal value);

// ARITHMETICS
int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
void summ(s21_big_decimal big_val1, s21_big_decimal big_val2, s21_big_decimal *res);
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal* result);
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
void s21_perform_division(s21_decimal dividend, s21_decimal divisor, s21_decimal *quotient, s21_decimal *remainder);
int s21_bank_round(s21_decimal *quotient, s21_decimal *remainder, s21_decimal divisor);

// COMPARISON
void s21_scale_to_power_of_ten(s21_decimal *decimal, int max_scale);
void multiply_by_ten(s21_decimal *decimal);
void divide_by_ten(s21_decimal *decimal);
void s21_scale_to_common(s21_decimal *a, s21_decimal *b);
int s21_is_equal(s21_decimal a, s21_decimal b);
int s21_is_not_equal(s21_decimal a, s21_decimal b);
int s21_is_less(s21_decimal a, s21_decimal b);
int s21_is_less_or_equal(s21_decimal a, s21_decimal b);
int s21_is_greater(s21_decimal a, s21_decimal b);
int s21_is_greater_or_equal(s21_decimal a, s21_decimal b);

//NORMALISATION
int normalisation(s21_big_decimal* value1, int scale1, s21_big_decimal* value2, int scale2, int* new_scale);
int overflow_check(s21_decimal *decimal);
int overflow_check_big_decimal(s21_big_decimal* decimal);
void printArray(s21_decimal result);


// OTHER FUNCTIONS
int s21_negate(s21_decimal value, s21_decimal *result);
int s21_truncate(s21_decimal value, s21_decimal *result);
int s21_floor(s21_decimal value, s21_decimal *result);
int s21_round(s21_decimal value, s21_decimal *result);

// CONVERTORS

int s21_from_int_to_decimal(int src, s21_decimal *dst);
int s21_from_float_to_decimal(float src, s21_decimal *dst);
int s21_from_decimal_to_int(s21_decimal src, int *dst);
int s21_from_decimal_to_float(s21_decimal src, float *dst);

#endif