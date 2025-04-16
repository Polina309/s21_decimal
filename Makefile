CC = gcc
CFLAGS = -Wall -Werror -Wextra -g -fstack-protector
LDFLAGS = -no-pie
CHECK_FLAGS = -lcheck -lsubunit -lm -lpthread
GCOVF = -fprofile-arcs -ftest-coverage

SOURCES = normalisation/normalisation.c normalisation/overflow.c \
           base_function/big_get_bit.c base_function/big_set_bit.c \
           base_function/set_bit.c \
           base_function/set_sign.c base_function/get_sign.c base_function/big_is_less.c\
           base_function/set_scale.c base_function/get_scale.c \
           base_function/convert_to_big_decimal.c base_function/is_zero.c \
           base_function/null_decimal.c base_function/inverse.c arithmetics/s21_add.c \
           arithmetics/summ.c arithmetics/s21_mul.c arithmetics/s21_sub.c arithmetics/s21_div.c\
           comparison/comparison.c \
           other_function/s21_truncate.c other_function/s21_floor.c \
           other_function/s21_negate.c other_function/s21_round.c \
           convertors.c


OBJECTS = $(SOURCES:.c=.o)

TEST_SOURCES = ./test/tests.c
TEST_OBJECTS = $(TEST_SOURCES:.c=.o)

EXECUTABLE = s21_decimal
TEST_EXECUTABLE = ./test/test_s21_decimal

s21_decimal.a: $(OBJECTS)
	ar rcs s21_decimal.a $(OBJECTS)
	ranlib s21_decimal.a

all: clean s21_decimal.a

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(CFLAGS) s21_decimal.c $(OBJECTS) -o ./obj/$@ -lm

test: $(TEST_EXECUTABLE)
	$(TEST_EXECUTABLE)

$(TEST_EXECUTABLE): $(OBJECTS) $(TEST_OBJECTS)
	$(CC) $(CFLAGS) $(GCOVF) $(SOURCES) $(TEST_OBJECTS) -o $@ $(CHECK_FLAGS)

gcov_report: clean test
	lcov --directory . --capture --output-file coverage.info
	genhtml coverage.info --output-directory out
	xdg-open out/index.html || open out/index.html

clean:
	rm -f $(OBJECTS) $(EXECUTABLE) $(TEST_OBJECTS) $(TEST_EXECUTABLE) *.
	rm -rf ./*.gcda ./*/*.gcno *.gcno *.css *.html *.info ./*.o ./*.a
	rm -d -rf out

.PHONY: all clean
