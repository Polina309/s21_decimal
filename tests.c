#include <check.h>
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

#include "./../s21_decimal.h"

START_TEST(test_s21_is_less) {
  s21_decimal a = {{1, 0, 0, 0}};
  s21_decimal b = {{2, 0, 0, 0}};
  s21_decimal c = {{1, 0, 0, 0x80000000}};  // -1
  s21_decimal large_num = {{0xFFFFFFFF, 0, 0, 0}};
  s21_decimal different_scale_1 = {{1, 0, 0, 0x01000000}};  // Scale = 1
  s21_decimal different_scale_2 = {{100, 0, 0, 0}};         // Scale = 0
  s21_decimal max_value = {{UINT_MAX, UINT_MAX, UINT_MAX, 0}};
  s21_decimal min_value = {{0, 0, 0, 0}};
  s21_decimal negative_1 = {{1, 0, 0, 0x80000000}};
  s21_decimal negative_2 = {{2, 0, 0, 0x80000000}};
  s21_decimal negative_3 = {{1, 0, 0, 0xFFFF0000}};  // -1.5

  // Базовые случаи
  ck_assert_int_eq(s21_is_less(a, b), 1);
  ck_assert_int_eq(s21_is_less(b, a), 0);
  ck_assert_int_eq(s21_is_less(a, a), 0);
  ck_assert_int_eq(s21_is_less(c, a), 1);
  ck_assert_int_eq(s21_is_less(a, c), 0);

  // Доп случаи
  ck_assert_int_eq(s21_is_less(max_value, max_value), 0);
  ck_assert_int_eq(s21_is_less(min_value, min_value), 0);
  ck_assert_int_eq(s21_is_less(large_num, c), 0);
  ck_assert_int_eq(s21_is_less(c, large_num), 1);
  ck_assert_int_eq(s21_is_less(different_scale_1, different_scale_2), 1);
  ck_assert_int_eq(s21_is_less(different_scale_2, different_scale_1), 0);

  // Отрицательные
  ck_assert_int_eq(s21_is_less(negative_1, negative_2), 0);
  ck_assert_int_eq(s21_is_less(negative_2, negative_1), 1);
  ck_assert_int_eq(s21_is_less(negative_1, negative_1), 0);
  ck_assert_int_eq(s21_is_less(negative_1, negative_3), 0);
  ck_assert_int_eq(s21_is_less(negative_3, negative_1), 1);
}
END_TEST

START_TEST(test_s21_is_less_or_equal) {
  s21_decimal a = {{3, 0, 0, 0}};
  s21_decimal b = {{3, 0, 0, 0}};
  s21_decimal c = {{4, 0, 0, 0}};
  s21_decimal d = {{3, 0, 0, 0x80000000}};
  s21_decimal large_num = {{UINT_MAX, 0, 0, 0}};
  s21_decimal small_num = {{1, 0, 0, 0}};
  s21_decimal different_scale_1 = {{1, 0, 0, 0x01000000}};  // Scale = 1
  s21_decimal different_scale_2 = {{100, 0, 0, 0}};         // Scale = 0
  s21_decimal max_value = {{UINT_MAX, UINT_MAX, UINT_MAX, 0}};
  s21_decimal min_value = {{0, 0, 0, 0}};
  s21_decimal negative_1 = {{1, 0, 0, 0x80000000}};
  s21_decimal negative_2 = {{2, 0, 0, 0x80000000}};

  // Базовые случаи
  ck_assert_int_eq(s21_is_less_or_equal(a, b), 1);
  ck_assert_int_eq(s21_is_less_or_equal(a, c), 1);
  ck_assert_int_eq(s21_is_less_or_equal(c, a), 0);
  ck_assert_int_eq(s21_is_less_or_equal(d, a), 1);
  ck_assert_int_eq(s21_is_less_or_equal(a, d), 0);

  // Доп случаи
  ck_assert_int_eq(s21_is_less_or_equal(large_num, small_num), 0);
  ck_assert_int_eq(s21_is_less_or_equal(small_num, large_num), 1);
  ck_assert_int_eq(s21_is_less_or_equal(different_scale_1, different_scale_2),
                   1);
  ck_assert_int_eq(s21_is_less_or_equal(different_scale_2, different_scale_1),
                   0);
  ck_assert_int_eq(s21_is_less_or_equal(max_value, max_value), 1);
  ck_assert_int_eq(s21_is_less_or_equal(min_value, min_value), 1);

  // Отрицательные
  ck_assert_int_eq(s21_is_less_or_equal(negative_1, negative_2), 0);
  ck_assert_int_eq(s21_is_less_or_equal(negative_2, negative_1), 1);
}
END_TEST

START_TEST(test_s21_is_greater) {
  s21_decimal a = {{5, 0, 0, 0}};
  s21_decimal b = {{4, 0, 0, 0}};
  s21_decimal c = {{5, 0, 0, 0x80000000}};
  s21_decimal large_num = {{UINT_MAX, 0, 0, 0}};
  s21_decimal small_num = {{1, 0, 0, 0}};
  s21_decimal different_scale_1 = {{1, 0, 0, 0x01000000}};  // Scale = 1
  s21_decimal different_scale_2 = {{100, 0, 0, 0}};         // Scale = 0
  s21_decimal max_value = {{UINT_MAX, UINT_MAX, UINT_MAX, 0}};
  s21_decimal min_value = {{0, 0, 0, 0}};
  s21_decimal negative_1 = {{1, 0, 0, 0x80000000}};
  s21_decimal negative_2 = {{2, 0, 0, 0x80000000}};

  // Базовые случаи
  ck_assert_int_eq(s21_is_greater(a, b), 1);
  ck_assert_int_eq(s21_is_greater(b, a), 0);
  ck_assert_int_eq(s21_is_greater(a, a), 0);
  ck_assert_int_eq(s21_is_greater(a, c), 1);
  ck_assert_int_eq(s21_is_greater(c, a), 0);

  // Доп случаи
  ck_assert_int_eq(s21_is_greater(large_num, small_num), 1);
  ck_assert_int_eq(s21_is_greater(small_num, large_num), 0);
  ck_assert_int_eq(s21_is_greater(different_scale_2, different_scale_1), 1);
  ck_assert_int_eq(s21_is_greater(different_scale_1, different_scale_2), 0);
  ck_assert_int_eq(s21_is_greater(max_value, max_value), 0);
  ck_assert_int_eq(s21_is_greater(min_value, min_value), 0);

  // Отрицательные
  ck_assert_int_eq(s21_is_greater(negative_1, negative_2), 1);
  ck_assert_int_eq(s21_is_greater(negative_2, negative_1), 0);
  ck_assert_int_eq(s21_is_greater(negative_1, negative_1), 0);
}
END_TEST

START_TEST(test_s21_is_greater_or_equal) {
  s21_decimal a = {{6, 0, 0, 0}};
  s21_decimal b = {{6, 0, 0, 0}};
  s21_decimal c = {{5, 0, 0, 0}};
  s21_decimal d = {{6, 0, 0, 0x80000000}};
  s21_decimal large_num = {{UINT_MAX, 0, 0, 0}};
  s21_decimal small_num = {{1, 0, 0, 0x80000000}};
  s21_decimal different_scale_1 = {{1, 0, 0, 0x01000000}};  // Scale = 1
  s21_decimal different_scale_2 = {{100, 0, 0, 0}};         // Scale = 0
  s21_decimal max_value = {{UINT_MAX, UINT_MAX, UINT_MAX, 0}};
  s21_decimal min_value = {{0, 0, 0, 0}};
  s21_decimal negative_1 = {{1, 0, 0, 0x80000000}};
  s21_decimal negative_2 = {{2, 0, 0, 0x80000000}};

  // Базовые случаи
  ck_assert_int_eq(s21_is_greater_or_equal(a, b), 1);
  ck_assert_int_eq(s21_is_greater_or_equal(a, c), 1);
  ck_assert_int_eq(s21_is_greater_or_equal(c, a), 0);
  ck_assert_int_eq(s21_is_greater_or_equal(a, d), 1);
  ck_assert_int_eq(s21_is_greater_or_equal(d, a), 0);

  // Доп случаи
  ck_assert_int_eq(s21_is_greater_or_equal(large_num, small_num), 1);
  ck_assert_int_eq(s21_is_greater_or_equal(small_num, large_num), 0);
  ck_assert_int_eq(
      s21_is_greater_or_equal(different_scale_2, different_scale_1), 1);
  ck_assert_int_eq(
      s21_is_greater_or_equal(different_scale_1, different_scale_2), 0);
  ck_assert_int_eq(s21_is_greater_or_equal(max_value, max_value), 1);
  ck_assert_int_eq(s21_is_greater_or_equal(min_value, min_value), 1);

  // Отрицательные
  ck_assert_int_eq(s21_is_greater_or_equal(negative_1, negative_2), 1);
  ck_assert_int_eq(s21_is_greater_or_equal(negative_2, negative_1), 0);
}
END_TEST

START_TEST(test_s21_is_equal) {
  s21_decimal a = {{7, 0, 0, 0}};
  s21_decimal b = {{7, 0, 0, 0}};
  s21_decimal c = {{8, 0, 0, 0}};
  s21_decimal d = {{7, 0, 0, 0x80000000}};
  s21_decimal large_num = {{INT_MAX, 0, 0, 0}};
  s21_decimal small_num = {{INT_MIN, 0, 0, 0}};
  s21_decimal different_scale_1 = {{1, 0, 0, 0x01000000}};  // Scale = 1
  s21_decimal different_scale_2 = {{100, 0, 0, 0}};         // Scale = 0
  s21_decimal max_value = {{UINT_MAX, UINT_MAX, UINT_MAX, 0}};
  s21_decimal min_value = {{0, 0, 0, 0}};
  s21_decimal negative_1 = {{1, 0, 0, 0x80000000}};
  s21_decimal negative_2 = {{2, 0, 0, 0x80000000}};

  // Базовые случаи
  ck_assert_int_eq(s21_is_equal(a, b), 1);
  ck_assert_int_eq(s21_is_equal(a, c), 0);
  ck_assert_int_eq(s21_is_equal(c, a), 0);
  ck_assert_int_eq(s21_is_equal(a, d), 0);
  ck_assert_int_eq(s21_is_equal(d, a), 0);

  // Доп случаи
  ck_assert_int_eq(s21_is_equal(large_num, small_num), 0);
  ck_assert_int_eq(s21_is_equal(small_num, large_num), 0);
  ck_assert_int_eq(s21_is_equal(different_scale_2, different_scale_1), 0);
  ck_assert_int_eq(s21_is_equal(different_scale_1, different_scale_2), 0);
  ck_assert_int_eq(s21_is_equal(max_value, max_value), 1);
  ck_assert_int_eq(s21_is_equal(min_value, min_value), 1);

  // Отрицательные
  ck_assert_int_eq(s21_is_equal(negative_1, negative_2), 0);
  ck_assert_int_eq(s21_is_equal(negative_2, negative_1), 0);
}
END_TEST

START_TEST(test_s21_is_not_equal) {
  s21_decimal a = {{9, 0, 0, 0}};
  s21_decimal b = {{10, 0, 0, 0}};
  s21_decimal c = {{9, 0, 0, 0x80000000}};
  s21_decimal large_num = {{INT_MAX, 0, 0, 0}};
  s21_decimal small_num = {{INT_MIN, 0, 0, 0}};
  s21_decimal different_scale_1 = {{1, 0, 0, 0x01000000}};  // Scale = 1
  s21_decimal different_scale_2 = {{100, 0, 0, 0}};         // Scale = 0
  s21_decimal max_value = {{UINT_MAX, UINT_MAX, UINT_MAX, 0}};
  s21_decimal min_value = {{0, 0, 0, 0}};
  s21_decimal negative_1 = {{1, 0, 0, 0x80000000}};
  s21_decimal negative_2 = {{2, 0, 0, 0x80000000}};

  // Базовые случаи
  ck_assert_int_eq(s21_is_not_equal(a, b), 1);
  ck_assert_int_eq(s21_is_not_equal(a, a), 0);
  ck_assert_int_eq(s21_is_not_equal(a, c), 1);
  ck_assert_int_eq(s21_is_not_equal(c, c), 0);
  ck_assert_int_eq(s21_is_not_equal(b, a), 1);

  // Доп случаи
  ck_assert_int_eq(s21_is_not_equal(large_num, small_num), 1);
  ck_assert_int_eq(s21_is_not_equal(small_num, large_num), 1);
  ck_assert_int_eq(s21_is_not_equal(different_scale_1, different_scale_2), 1);
  ck_assert_int_eq(s21_is_not_equal(different_scale_2, different_scale_1), 1);
  ck_assert_int_eq(s21_is_not_equal(max_value, max_value), 0);
  ck_assert_int_eq(s21_is_not_equal(min_value, min_value), 0);

  // Отрицательные
  ck_assert_int_eq(s21_is_not_equal(negative_1, negative_2), 1);
  ck_assert_int_eq(s21_is_not_equal(negative_2, negative_1), 1);
}
END_TEST

START_TEST(test_s21_div) {
  s21_decimal a = {{10, 0, 0, 0}};
  s21_decimal b = {{2, 0, 0, 0}};
  s21_decimal c = {{3, 0, 0, 0}};
  s21_decimal d = {{0, 0, 0, 0}};
  s21_decimal negative_a = {{10, 0, 0, 0x80000000}};
  s21_decimal negative_b = {{2, 0, 0, 0x80000000}};
  s21_decimal result = {{0, 0, 0, 0}};
  s21_decimal scale_1 = {{100, 0, 0, 0x01000000}};  // Scale = 1
  s21_decimal scale_2 = {{10, 0, 0, 0}};            // Scale = 0
  s21_decimal large_number = {{1000000, 0, 0, 0}};
  s21_decimal max_value = {{2147483647U, 0, 0, 0}};
  s21_decimal min_value = {{2147483648U, 0, 0, 0x80000000}};
  s21_decimal f = {{1, 0, 0, 0}};

  unsigned long long large_value1 = 9223372036854775807ULL;
  unsigned long long large_value2 = 9223372036854775807ULL;
  unsigned long long small_value = 1000000000000ULL;

  s21_decimal large_decimal1 = {{(unsigned int)(large_value1 & 0xFFFFFFFF),
                                 (unsigned int)(large_value1 >> 32), 0, 0}};
  s21_decimal large_decimal2 = {{(unsigned int)(large_value2 & 0xFFFFFFFF),
                                 (unsigned int)(large_value2 >> 32), 0, 0}};
  s21_decimal small_decimal = {{(unsigned int)(small_value & 0xFFFFFFFF),
                                (unsigned int)(small_value >> 32), 0, 0}};

  s21_decimal q = {{100000000, 0, 0, 0}};
  s21_decimal e = {{1000000, 0, 0, 0}};
  s21_decimal large_a = {{1073741823, 0, 0, 0}};
  s21_decimal y = {{4, 0, 0, 0}};
  s21_decimal u = {{11, 0, 0, 0}};

  unsigned long long overflow_value = 18446744073709551615ULL;
  s21_decimal overflow_decimal = {{(unsigned int)(overflow_value & 0xFFFFFFFF),
                                   (unsigned int)(overflow_value >> 32), 0, 0}};
  s21_decimal overflow_decimal1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  s21_decimal neg_overflow = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};

  // Базовые случаи
  ck_assert_int_eq(s21_div(a, b, &result), 0);  // 10 / 2
  ck_assert_int_eq(result.bits[0], 5);

  ck_assert_int_eq(s21_div(a, a, &result), 0);  // 10 / 10
  ck_assert_int_eq(result.bits[0], 1);

  ck_assert_int_eq(s21_div(c, b, &result), 0);  // 3 / 2 = 2
  ck_assert_int_eq(result.bits[0], 2);

  ck_assert_int_eq(s21_div(a, c, &result), 0);  // 10 / 3 = 3
  ck_assert_int_eq(result.bits[0], 3);

  ck_assert_int_eq(s21_div(b, c, &result), 0);  // 2 / 3 = 1
  ck_assert_int_eq(result.bits[0], 1);

  ck_assert_int_eq(s21_div(a, large_number, &result), 0);  // 10 / 1000000 = 0
  ck_assert_int_eq(result.bits[0], 0);

  // Деление на 0
  ck_assert_int_eq(s21_div(a, d, &result), 3);  // 10 / 0, ошибка

  ck_assert_int_eq(s21_div(d, d, &result), 3);  // 0 / 0, ошибка

  ck_assert_int_eq(s21_div(d, a, &result), 0);  // 0 / 10 = 0, без ошибки
  ck_assert_int_eq(result.bits[0], 0);

  // С отрицательными
  ck_assert_int_eq(s21_div(negative_a, b, &result), 0);  // -10 / 2 = -5
  ck_assert_int_eq(result.bits[0], 5);
  ck_assert_int_eq(result.bits[3],
                   0x80000000);  // знак - (дополнение до 2:-2^31)

  ck_assert_int_eq(s21_div(a, negative_b, &result), 0);  // 10 / -2 = -5
  ck_assert_int_eq(result.bits[0], 5);
  ck_assert_int_eq(result.bits[3], 0x80000000);  // знак -

  ck_assert_int_eq(s21_div(negative_a, negative_b, &result),
                   0);  // -10 / -2 = 5
  ck_assert_int_eq(result.bits[0], 5);
  ck_assert_int_eq(result.bits[3], 0);  // знак +

  // Разный масштаб
  ck_assert_int_eq(s21_div(scale_1, scale_2, &result), 0);  // 100 / 10 = 10
  ck_assert_int_eq(result.bits[0], 10);

  // Проверка деления больших значений: 32- и 64-битных
  ck_assert_int_eq(s21_div(max_value, f, &result), 0);
  ck_assert_uint_eq(result.bits[0], 2147483647);

  ck_assert_int_eq(s21_div(max_value, b, &result), 0);
  ck_assert_int_eq(result.bits[0], 1073741824);

  ck_assert_int_eq(s21_div(max_value, max_value, &result), 0);
  ck_assert_uint_eq(result.bits[0], 1);

  ck_assert_int_eq(s21_div(min_value, min_value, &result), 0);
  ck_assert_uint_eq(result.bits[0], 1);

  ck_assert_int_eq(s21_div(max_value, min_value, &result), 0);
  ck_assert_int_eq(result.bits[0], 1);
  ck_assert_int_eq(result.bits[3], 0x80000000);

  ck_assert_int_eq(s21_div(min_value, max_value, &result), 0);
  ck_assert_int_eq(result.bits[0], 1);
  ck_assert_int_eq(result.bits[3], 0x80000000);

  ck_assert_int_eq(s21_div(large_decimal1, large_decimal2, &result), 0);
  ck_assert_uint_eq(result.bits[0], 1);

  ck_assert_int_eq(s21_div(large_decimal1, small_decimal, &result), 0);
  ck_assert_int_eq(result.bits[0], large_value1 / small_value);

  ck_assert_int_eq(s21_div(large_decimal1, f, &result), 1);

  ck_assert_int_eq(s21_div(q, f, &result), 0);
  ck_assert_int_eq(result.bits[0], 100000000);

  ck_assert_int_eq(s21_div(q, e, &result), 0);
  ck_assert_int_eq(result.bits[0], 100);

  // Проверка банковского округления
  ck_assert_int_eq(s21_div(large_a, y, &result), 0);
  ck_assert_int_eq(result.bits[0], 268435456);

  ck_assert_int_eq(s21_div(a, y, &result), 0);  // 10 / 4 = 2,5 = 2
  ck_assert_int_eq(result.bits[0], 2);

  ck_assert_int_eq(s21_div(u, b, &result), 0);  // 11 / 2 = 5,5 = 6
  ck_assert_int_eq(result.bits[0], 6);

  // Проверка переполнения при делении
  ck_assert_int_eq(s21_div(overflow_decimal, f, &result), 1);

  ck_assert_int_eq(s21_div(overflow_decimal1, f, &result), 1);

  ck_assert_int_eq(s21_div(neg_overflow, f, &result), 2);

  ck_assert_int_eq(s21_div(large_decimal1, f, &result), 1);

  ck_assert_int_eq(s21_div(min_value, f, &result), 2);
}
END_TEST

START_TEST(test_s21_add) {
  s21_decimal a = {{5, 0, 0, 0}};         // 5
  s21_decimal b = {{3, 0, 0, 0}};         // 3
  s21_decimal c = {0};                    // Результат
  s21_decimal expected = {{8, 0, 0, 0}};  // 5 + 3 = 8

  // Сложение положительных чисел
  ck_assert_int_eq(s21_add(a, b, &c), 0);
  ck_assert_int_eq(c.bits[0], expected.bits[0]);
  ck_assert_int_eq(c.bits[1], expected.bits[1]);
  ck_assert_int_eq(c.bits[2], expected.bits[2]);
  ck_assert_int_eq(c.bits[3], expected.bits[3]);

  // Сложение отрицательных чисел
  s21_decimal d = {{5, 0, 0, 0x80000000}};             // -5
  s21_decimal e = {{3, 0, 0, 0x80000000}};             // -3
  s21_decimal expected_neg = {{8, 0, 0, 0x80000000}};  // -5 + (-3) = -8
  ck_assert_int_eq(s21_add(d, e, &c), 0);
  ck_assert_int_eq(c.bits[0], expected_neg.bits[0]);
  ck_assert_int_eq(c.bits[3], expected_neg.bits[3]);

  // Сложение чисел с разными знаками
  s21_decimal f = {{5, 0, 0, 0}};              // 5
  s21_decimal g = {{3, 0, 0, 0x80000000}};     // -3
  s21_decimal expected_diff = {{2, 0, 0, 0}};  // 5 + (-3) = 2
  ck_assert_int_eq(s21_add(f, g, &c), 0);
  ck_assert_int_eq(c.bits[0], expected_diff.bits[0]);

  // Сложение чисел с разными масштабами
  s21_decimal h = {{5, 0, 0, 0x00010000}};                // 0.5
  s21_decimal i = {{3, 0, 0, 0x00020000}};                // 0.03
  s21_decimal expected_scale = {{53, 0, 0, 0x00020000}};  // 0.5 + 0.03 = 0.53
  ck_assert_int_eq(s21_add(h, i, &c), 0);
  ck_assert_int_eq(c.bits[0], expected_scale.bits[0]);
  ck_assert_int_eq(c.bits[3], expected_scale.bits[3]);

  // Переполнение
  s21_decimal max = {
      {UINT_MAX, UINT_MAX, UINT_MAX, 0}};  // Максимальное значение
  s21_decimal one = {{1, 0, 0, 0}};  // 1
  ck_assert_int_eq(s21_add(max, one, &c), 1);  // Ожидаем ошибку переполнения
}
END_TEST

START_TEST(test_s21_sub) {
  s21_decimal a = {{5, 0, 0, 0}};         // 5
  s21_decimal b = {{3, 0, 0, 0}};         // 3
  s21_decimal c = {0};                    // Результат
  s21_decimal expected = {{2, 0, 0, 0}};  // 5 - 3 = 2

  // Вычитание положительных чисел
  ck_assert_int_eq(s21_sub(a, b, &c), 0);
  ck_assert_int_eq(c.bits[0], expected.bits[0]);

  // Вычитание отрицательных чисел
  s21_decimal d = {{5, 0, 0, 0x80000000}};             // -5
  s21_decimal e = {{3, 0, 0, 0x80000000}};             // -3
  s21_decimal expected_neg = {{2, 0, 0, 0x80000000}};  // -5 - (-3) = -2
  ck_assert_int_eq(s21_sub(d, e, &c), 0);
  ck_assert_int_eq(c.bits[0], expected_neg.bits[0]);
  ck_assert_int_eq(c.bits[3], expected_neg.bits[3]);

  // Вычитание чисел с разными знаками
  s21_decimal f = {{5, 0, 0, 0}};              // 5
  s21_decimal g = {{3, 0, 0, 0x80000000}};     // -3
  s21_decimal expected_diff = {{8, 0, 0, 0}};  // 5 - (-3) = 8
  ck_assert_int_eq(s21_sub(f, g, &c), 0);
  ck_assert_int_eq(c.bits[0], expected_diff.bits[0]);

  // Вычитание чисел с разными масштабами
  s21_decimal h = {{5, 0, 0, 0x00010000}};                // 0.5
  s21_decimal i = {{3, 0, 0, 0x00020000}};                // 0.03
  s21_decimal expected_scale = {{47, 0, 0, 0x00020000}};  // 0.5 - 0.03 = 0.47
  ck_assert_int_eq(s21_sub(h, i, &c), 0);
  ck_assert_int_eq(c.bits[0], expected_scale.bits[0]);
  ck_assert_int_eq(c.bits[3], expected_scale.bits[3]);

  // Переполнение
  s21_decimal min = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF,
                      0x80000000}};  // Минимальное значение
  s21_decimal one = {{1, 0, 0, 0}};  // 1
  s21_decimal j = {0};               // Результат
  ck_assert_int_eq(s21_sub(min, one, &j), 1);  // Ожидаем ошибку переполнения
}
END_TEST

START_TEST(test_s21_mul) {
  s21_decimal a = {{5, 0, 0, 0}};          // 5
  s21_decimal b = {{3, 0, 0, 0}};          // 3
  s21_decimal c = {0};                     // Результат
  s21_decimal expected = {{15, 0, 0, 0}};  // 5 * 3 = 15

  // Умножение положительных чисел
  ck_assert_int_eq(s21_mul(a, b, &c), 0);
  ck_assert_int_eq(c.bits[0], expected.bits[0]);

  // Умножение отрицательных чисел
  s21_decimal d = {{5, 0, 0, 0x80000000}};     // -5
  s21_decimal e = {{3, 0, 0, 0x80000000}};     // -3
  s21_decimal expected_neg = {{15, 0, 0, 0}};  // -5 * -3 = 15
  ck_assert_int_eq(s21_mul(d, e, &c), 0);
  ck_assert_int_eq(c.bits[0], expected_neg.bits[0]);

  // Умножение чисел с разными знаками
  s21_decimal f = {{5, 0, 0, 0}};                        // 5
  s21_decimal g = {{3, 0, 0, 0x80000000}};               // -3
  s21_decimal expected_diff = {{15, 0, 0, 0x80000000}};  // 5 * (-3) = -15
  ck_assert_int_eq(s21_mul(f, g, &c), 0);
  ck_assert_int_eq(c.bits[0], expected_diff.bits[0]);
  ck_assert_int_eq(c.bits[3], expected_diff.bits[3]);

  // Умножение чисел с разными масштабами
  s21_decimal h = {{5, 0, 0, 0x00010000}};                // 0.5
  s21_decimal i = {{3, 0, 0, 0x00010000}};                // 0.3
  s21_decimal expected_scale = {{15, 0, 0, 0x00020000}};  // 0.5 * 0.3 = 0.15
  ck_assert_int_eq(s21_mul(h, i, &c), 0);
  ck_assert_int_eq(c.bits[0], expected_scale.bits[0]);
  ck_assert_int_eq(c.bits[3], expected_scale.bits[3]);

  // Переполнение
  s21_decimal max = {
      {UINT_MAX, UINT_MAX, UINT_MAX, 0}};  // Максимальное значение
  s21_decimal two = {{2, 0, 0, 0}};  // 2
  ck_assert_int_eq(s21_mul(max, two, &c), 1);  // Ожидаем ошибку переполнения
}
END_TEST

START_TEST(test_s21_negate_1) {
  s21_decimal value = {{1, 0, 0, 0}};              // 1
  s21_decimal expected = {{1, 0, 0, 0x80000000}};  // -1
  s21_decimal result;
  s21_negate(value, &result);
  ck_assert_mem_eq(&result, &expected, sizeof(s21_decimal));
}
END_TEST

START_TEST(test_s21_negate_2) {
  s21_decimal value = {{0, 0, 0, 0}};     // 0
  s21_decimal expected = {{0, 0, 0, 0}};  // 0
  s21_decimal result;
  s21_negate(value, &result);
  ck_assert_mem_eq(&result, &expected, sizeof(s21_decimal));
}
END_TEST

START_TEST(test_s21_negate_3) {
  s21_decimal value = {{1, 0, 0, 0x80000000}};  // -1
  s21_decimal expected = {{1, 0, 0, 0}};        // 1
  s21_decimal result;
  s21_negate(value, &result);
  ck_assert_mem_eq(&result, &expected, sizeof(s21_decimal));
}
END_TEST

START_TEST(test_s21_negate_4) {
  s21_decimal value = {{INT_MAX, 0, 0, 0}};              // INT_MAX
  s21_decimal expected = {{INT_MAX, 0, 0, 0x80000000}};  // -INT_MAX
  s21_decimal result;
  s21_negate(value, &result);
  ck_assert_mem_eq(&result, &expected, sizeof(s21_decimal));
}
END_TEST

START_TEST(test_s21_negate_5) {
  s21_decimal value = {{INT_MAX, 0, 0, 0x80000000}};  // -INT_MAX
  s21_decimal expected = {{INT_MAX, 0, 0, 0}};        // INT_MAX
  s21_decimal result;
  s21_negate(value, &result);
  ck_assert_mem_eq(&result, &expected, sizeof(s21_decimal));
}
END_TEST

START_TEST(test_s21_truncate_1) {
  s21_decimal value = {{12345, 0, 0, 0x00020000}};  // 123.45 (scale = 2)
  s21_decimal expected = {{123, 0, 0, 0}};  // 123 (целая часть)
  s21_decimal result;
  s21_truncate(value, &result);
  ck_assert_mem_eq(&result, &expected, sizeof(s21_decimal));
}
END_TEST

START_TEST(test_s21_truncate_2) {
  s21_decimal value = {{100, 0, 0, 0x00010000}};  // 10.0 (scale = 1)
  s21_decimal expected = {{10, 0, 0, 0}};         // 10
  s21_decimal result;
  s21_truncate(value, &result);
  ck_assert_mem_eq(&result, &expected, sizeof(s21_decimal));
}
END_TEST

START_TEST(test_s21_truncate_3) {
  s21_decimal value = {{1, 0, 0, 0}};  // 1 (без дробной части)
  s21_decimal expected = {{1, 0, 0, 0}};  // 1
  s21_decimal result;
  s21_truncate(value, &result);
  ck_assert_mem_eq(&result, &expected, sizeof(s21_decimal));
}
END_TEST

START_TEST(test_s21_truncate_4) {
  s21_decimal value = {
      {123456789, 0, 0, 0x001C0000}};     // 0.000...00123456789 (scale = 28)
  s21_decimal expected = {{0, 0, 0, 0}};  // 0 (целая часть)
  s21_decimal result;
  s21_truncate(value, &result);
  ck_assert_mem_eq(&result, &expected, sizeof(s21_decimal));
}
END_TEST

START_TEST(test_s21_truncate_5) {
  s21_decimal value = {{567, 0, 0, 0x80020000}};   // -5.67 (scale = 2)
  s21_decimal expected = {{5, 0, 0, 0x80000000}};  // -5 (целая часть)
  s21_decimal result;
  s21_truncate(value, &result);
  ck_assert_mem_eq(&result, &expected, sizeof(s21_decimal));
}
END_TEST

// floor тесты

// макс положительное целое число
START_TEST(test_s21_floor_1) {
  s21_decimal value = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  s21_decimal expected = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x00000000}};
  s21_decimal result = {0};

  int return_code = s21_floor(value, &result);

  ck_assert_int_eq(result.bits[0], expected.bits[0]);
  ck_assert_int_eq(result.bits[1], expected.bits[1]);
  ck_assert_int_eq(result.bits[2], expected.bits[2]);
  ck_assert_int_eq(result.bits[3], expected.bits[3]);
  ck_assert_int_eq(return_code, 0);
}

// макс отрицательное целое число
START_TEST(test_s21_floor_2) {
  s21_decimal value = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  s21_decimal expected = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  s21_decimal result = {0};

  int return_code = s21_floor(value, &result);

  ck_assert_int_eq(result.bits[0], expected.bits[0]);
  ck_assert_int_eq(result.bits[1], expected.bits[1]);
  ck_assert_int_eq(result.bits[2], expected.bits[2]);
  ck_assert_int_eq(result.bits[3], expected.bits[3]);
  ck_assert_int_eq(return_code, 0);
}

// дробное положительное число
START_TEST(test_s21_floor_3) {
  s21_decimal value = {{0x9999999A, 0x99999999, 0x19999999, 0x001C0000}};
  s21_decimal expected = {{0x00000000, 0x00000000, 0x00000000, 0x00000000}};
  s21_decimal result = {0};

  int return_code = s21_floor(value, &result);

  ck_assert_int_eq(result.bits[0], expected.bits[0]);
  ck_assert_int_eq(result.bits[1], expected.bits[1]);
  ck_assert_int_eq(result.bits[2], expected.bits[2]);
  ck_assert_int_eq(result.bits[3], expected.bits[3]);
  ck_assert_int_eq(return_code, 0);
}

// дробное отрицательное число
START_TEST(test_s21_floor_4) {
  s21_decimal value = {{0x9999999A, 0x99999999, 0x19999999, 0x801C0000}};
  s21_decimal expected = {{0x00000001, 0x00000000, 0x00000000, 0x80000000}};
  s21_decimal result = {0};

  int return_code = s21_floor(value, &result);

  ck_assert_int_eq(result.bits[0], expected.bits[0]);
  ck_assert_int_eq(result.bits[1], expected.bits[1]);
  ck_assert_int_eq(result.bits[2], expected.bits[2]);
  ck_assert_int_eq(result.bits[3], expected.bits[3]);
  ck_assert_int_eq(return_code, 0);
}

START_TEST(test_s21_floor_5) {
  s21_decimal value = {{12123, 0, 0, 0x00020000}};  // 121.23 (scale = 2)
  s21_decimal expected = {{121, 0, 0, 0}};  // 121 (целая часть)
  s21_decimal result;
  s21_floor(value, &result);
  ck_assert_mem_eq(&result, &expected, sizeof(s21_decimal));
}
END_TEST

START_TEST(test_s21_floor_6) {
  s21_decimal value = {{190232, 0, 0, 0x00030000}};  // 190.232 (scale = 3)
  s21_decimal expected = {{190, 0, 0, 0}};           // 190
  s21_decimal result;
  s21_floor(value, &result);
  ck_assert_mem_eq(&result, &expected, sizeof(s21_decimal));
}
END_TEST

START_TEST(test_s21_floor_7) {
  s21_decimal value = {{1, 0, 0, 0}};  // 1 (без дробной части)
  s21_decimal expected = {{1, 0, 0, 0}};  // 1
  s21_decimal result;
  s21_floor(value, &result);
  ck_assert_mem_eq(&result, &expected, sizeof(s21_decimal));
}
END_TEST

START_TEST(test_s21_floor_8) {
  s21_decimal value = {
      {123456789, 0, 0, 0x001C0000}};     // 0.000...00123456789 (scale = 28)
  s21_decimal expected = {{0, 0, 0, 0}};  // 0 (целая часть)
  s21_decimal result;
  s21_floor(value, &result);
  ck_assert_mem_eq(&result, &expected, sizeof(s21_decimal));
}
END_TEST

START_TEST(test_s21_floor_9) {
  s21_decimal value = {{829, 0, 0, 0x80020000}};   // -8.29 (scale = 2)
  s21_decimal expected = {{9, 0, 0, 0x80000000}};  // -9 (целая часть)
  s21_decimal result;
  s21_floor(value, &result);
  ck_assert_mem_eq(&result, &expected, sizeof(s21_decimal));
}
END_TEST

// round тесты

// макс положительное целое число
START_TEST(test_s21_round_1) {
  s21_decimal value = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x0}};
  s21_decimal expected = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x00000000}};
  s21_decimal result = {0};

  int return_code = s21_round(value, &result);

  ck_assert_int_eq(result.bits[0], expected.bits[0]);
  ck_assert_int_eq(result.bits[1], expected.bits[1]);
  ck_assert_int_eq(result.bits[2], expected.bits[2]);
  ck_assert_int_eq(result.bits[3], expected.bits[3]);
  ck_assert_int_eq(return_code, 0);
}

// макс отрицательное целое число
START_TEST(test_s21_round_2) {
  s21_decimal value = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  s21_decimal expected = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0x80000000}};
  s21_decimal result = {0};

  int return_code = s21_round(value, &result);

  ck_assert_int_eq(result.bits[0], expected.bits[0]);
  ck_assert_int_eq(result.bits[1], expected.bits[1]);
  ck_assert_int_eq(result.bits[2], expected.bits[2]);
  ck_assert_int_eq(result.bits[3], expected.bits[3]);
  ck_assert_int_eq(return_code, 0);
}

// дробное положительное число
START_TEST(test_s21_round_3) {
  s21_decimal value = {
      {0x9999999A, 0x99999999, 0x19999999, 0x001C0000}};  // 0.7922812514...
  s21_decimal expected = {{1, 0, 0, 0}};                  // 1
  s21_decimal result = {0};

  int return_code = s21_round(value, &result);

  ck_assert_int_eq(result.bits[0], expected.bits[0]);
  ck_assert_int_eq(result.bits[1], expected.bits[1]);
  ck_assert_int_eq(result.bits[2], expected.bits[2]);
  ck_assert_int_eq(result.bits[3], expected.bits[3]);
  ck_assert_int_eq(return_code, 0);
}

// дробное отрицательное число
START_TEST(test_s21_round_4) {
  s21_decimal value = {{0x9999999A, 0x99999999, 0x19999999, 0x801C0000}};
  s21_decimal expected = {{0x00000001, 0x00000000, 0x00000000, 0x80000000}};
  s21_decimal result = {0};

  int return_code = s21_round(value, &result);

  ck_assert_int_eq(result.bits[0], expected.bits[0]);
  ck_assert_int_eq(result.bits[1], expected.bits[1]);
  ck_assert_int_eq(result.bits[2], expected.bits[2]);
  ck_assert_int_eq(result.bits[3], expected.bits[3]);
  ck_assert_int_eq(return_code, 0);
}

START_TEST(test_s21_round_5) {
  s21_decimal value = {{1350, 0, 0, 0x00020000}};  // 13.5 (scale = 2)
  s21_decimal expected = {{14, 0, 0, 0}};          // 14 (целая часть)
  s21_decimal result;
  s21_round(value, &result);
  ck_assert_mem_eq(&result, &expected, sizeof(s21_decimal));
}
END_TEST

START_TEST(test_s21_round_6) {
  s21_decimal value = {{74500, 0, 0, 0x00030000}};  // 74.5 (scale = 3)
  s21_decimal expected = {{74, 0, 0, 0}};           // 74
  s21_decimal result;
  s21_round(value, &result);
  ck_assert_mem_eq(&result, &expected, sizeof(s21_decimal));
}
END_TEST

START_TEST(test_s21_round_7) {
  s21_decimal value = {{1, 0, 0, 0}};  // 1 (без дробной части)
  s21_decimal expected = {{1, 0, 0, 0}};  // 1
  s21_decimal result;
  s21_round(value, &result);
  ck_assert_mem_eq(&result, &expected, sizeof(s21_decimal));
}
END_TEST

START_TEST(test_s21_round_8) {
  s21_decimal value = {
      {123456789, 0, 0, 0x001C0000}};     // 0.000...00123456789 (scale = 28)
  s21_decimal expected = {{0, 0, 0, 0}};  // 0 (целая часть)
  s21_decimal result;
  s21_round(value, &result);
  ck_assert_mem_eq(&result, &expected, sizeof(s21_decimal));
}
END_TEST

START_TEST(test_s21_round_9) {
  s21_decimal value = {{829, 0, 0, 0x80020000}};   // -8.29 (scale = 2)
  s21_decimal expected = {{8, 0, 0, 0x80000000}};  // -8 (целая часть)
  s21_decimal result;
  s21_round(value, &result);
  ck_assert_mem_eq(&result, &expected, sizeof(s21_decimal));
}
END_TEST

// преобразование

START_TEST(test_s21_from_int_to_decimal) {
  s21_decimal dst;

  // Тестируем положительное число
  int src = 1234;
  ck_assert_int_eq(s21_from_int_to_decimal(src, &dst), 0);
  ck_assert_int_eq(dst.bits[0],
                   1234);  // Проверяем, что число записано правильно

  // Тестируем отрицательное число
  src = -5678;
  ck_assert_int_eq(s21_from_int_to_decimal(src, &dst), 0);
  ck_assert_int_eq(dst.bits[0],
                   5678);  // Проверяем, что число записано как положительное
  ck_assert_int_eq(get_sign(dst),
                   1);  // Проверяем, что знак установлен как отрицательный

  // Тестируем 0
  src = 0;
  ck_assert_int_eq(s21_from_int_to_decimal(src, &dst), 0);
  ck_assert_int_eq(dst.bits[0],
                   0);  // Проверяем, что число 0 правильно преобразуется
}
END_TEST
START_TEST(test_s21_from_float_to_decimal) {
  s21_decimal dst;

  // Тестируем положительное число
  float src = 123.456;

  ck_assert_int_eq(s21_from_float_to_decimal(src, &dst), 0);
  ck_assert_int_eq(
      dst.bits[0],
      123456);  // Проверяем, что целая часть числа записана правильно
  ck_assert_int_eq(get_scale(dst),
                   3);  // Проверяем, что масштаб (scale) правильно установлен

  src = 12.3456;

  ck_assert_int_eq(s21_from_float_to_decimal(src, &dst), 0);
  ck_assert_int_eq(
      dst.bits[0],
      12346);  // Проверяем, что целая часть числа записана правильно
  ck_assert_int_eq(get_scale(dst), 3);

  // Тестируем отрицательное число
  src = -789.012;
  ck_assert_int_eq(s21_from_float_to_decimal(src, &dst), 0);
  ck_assert_int_eq(
      dst.bits[0],
      789012);  // Проверяем, что целая часть числа записана как положительная
  ck_assert_int_eq(get_sign(dst),
                   1);  // Проверяем, что знак установлен как отрицательный
  ck_assert_int_eq(get_scale(dst),
                   3);  // Проверяем, что масштаб правильно установлен

  // Тестируем очень маленькое число
  src = 1e-30;
  ck_assert_int_eq(s21_from_float_to_decimal(src, &dst),
                   1);  // Ожидаем ошибку (слишком малое значение)
}

END_TEST

START_TEST(test_s21_from_decimal_to_int) {
  s21_decimal src;
  int dst;

  // Тестируем положительное число
  src.bits[0] = 1234;
  ck_assert_int_eq(s21_from_decimal_to_int(src, &dst), 0);
  ck_assert_int_eq(dst, 1234);  // Проверяем, что число преобразовано правильно

  // Тестируем отрицательное число
  src.bits[0] = 5678;
  set_sign(&src, 1);  // Устанавливаем знак как отрицательный
  ck_assert_int_eq(s21_from_decimal_to_int(src, &dst), 0);
  ck_assert_int_eq(
      dst, -5678);  // Проверяем, что число преобразовано в отрицательное

  // Тестируем 0
  src.bits[0] = 0;
  ck_assert_int_eq(s21_from_decimal_to_int(src, &dst), 0);
  ck_assert_int_eq(dst, 0);  // Проверяем, что число 0 правильно преобразуется
}
END_TEST

START_TEST(test_s21_from_decimal_to_float) {
  s21_decimal src = {0};
  float dst;

  // Тестируем положительное число
  src.bits[0] = 1234;
  set_scale(&src, 3);  // Устанавливаем масштаб (например, для числа 1.234)
  ck_assert_int_eq(s21_from_decimal_to_float(src, &dst), 0);
  ck_assert_float_eq_tol(dst, 1.234,
                         1e-6);  // Проверяем, что число преобразовано корректно

  // Тестируем отрицательное число
  src.bits[0] = 5678;
  set_scale(&src, 3);  // Устанавливаем масштаб
  set_sign(&src, 1);  // Устанавливаем знак как отрицательный
  ck_assert_int_eq(s21_from_decimal_to_float(src, &dst), 0);
  ck_assert_float_eq(dst, -5.678);  // Проверяем, что число преобразовано
                                    // корректно и знак правильный

  // Тестируем 0
  src.bits[0] = 0;
  set_scale(&src, 0);  // Устанавливаем масштаб как 0
  ck_assert_int_eq(s21_from_decimal_to_float(src, &dst), 0);
  ck_assert_float_eq(dst,
                     0.0);  // Проверяем, что 0 преобразуется в 0.0 корректно
}
END_TEST

Suite *s21_decimal_suite(void) {
  Suite *s = suite_create("s21_decimal_tests");
  TCase *tc_core = tcase_create("Core");

  tcase_add_test(tc_core, test_s21_is_less);
  tcase_add_test(tc_core, test_s21_is_less_or_equal);
  tcase_add_test(tc_core, test_s21_is_greater);
  tcase_add_test(tc_core, test_s21_is_greater_or_equal);
  tcase_add_test(tc_core, test_s21_is_equal);
  tcase_add_test(tc_core, test_s21_is_not_equal);

  tcase_add_test(tc_core, test_s21_div);
  tcase_add_test(tc_core, test_s21_add);
  tcase_add_test(tc_core, test_s21_sub);
  tcase_add_test(tc_core, test_s21_mul);

  tcase_add_test(tc_core, test_s21_negate_1);
  tcase_add_test(tc_core, test_s21_negate_2);
  tcase_add_test(tc_core, test_s21_negate_3);
  tcase_add_test(tc_core, test_s21_negate_4);
  tcase_add_test(tc_core, test_s21_negate_5);
  tcase_add_test(tc_core, test_s21_truncate_1);
  tcase_add_test(tc_core, test_s21_truncate_2);
  tcase_add_test(tc_core, test_s21_truncate_3);
  tcase_add_test(tc_core, test_s21_truncate_4);
  tcase_add_test(tc_core, test_s21_truncate_5);
  tcase_add_test(tc_core, test_s21_floor_1);
  tcase_add_test(tc_core, test_s21_floor_2);
  tcase_add_test(tc_core, test_s21_floor_3);
  tcase_add_test(tc_core, test_s21_floor_4);
  tcase_add_test(tc_core, test_s21_floor_5);
  tcase_add_test(tc_core, test_s21_floor_6);
  tcase_add_test(tc_core, test_s21_floor_7);
  tcase_add_test(tc_core, test_s21_floor_8);
  tcase_add_test(tc_core, test_s21_floor_9);
  tcase_add_test(tc_core, test_s21_round_1);
  tcase_add_test(tc_core, test_s21_round_2);
  tcase_add_test(tc_core, test_s21_round_3);
  tcase_add_test(tc_core, test_s21_round_4);
  tcase_add_test(tc_core, test_s21_round_5);
  tcase_add_test(tc_core, test_s21_round_6);
  tcase_add_test(tc_core, test_s21_round_7);
  tcase_add_test(tc_core, test_s21_round_8);
  tcase_add_test(tc_core, test_s21_round_9);
  tcase_add_test(tc_core, test_s21_from_int_to_decimal);
  tcase_add_test(tc_core, test_s21_from_float_to_decimal);
  tcase_add_test(tc_core, test_s21_from_decimal_to_int);
  tcase_add_test(tc_core, test_s21_from_decimal_to_float);
  suite_add_tcase(s, tc_core);

  return s;
}

int main(void) {
  int number_failed;
  Suite *s = s21_decimal_suite();
  SRunner *sr = srunner_create(s);

  srunner_run_all(sr, CK_VERBOSE);
  number_failed = srunner_ntests_failed(sr);
  srunner_free(sr);

  return (number_failed == 0) ? 0 : 1;
}
