NAME = s21_smart_calc
CC = gcc
CC_FLAGS = -std=c11 -Wall -Wextra -Werror -g #-pedantic
GCOV_FLAGS = -L. -ls21_smart_calc --coverage
OS = $(shell uname)
ifeq ($(OS), Linux)
	CHECK_FLAGS = -lcheck -pthread -lrt -lm -lsubunit
else
	CHECK_FLAGS = $(shell pkg-config --libs --cflags check) -lm
endif

TEST_COMPILE = $(CC) $(CC_FLAGS) tests/*.c libs21_smart_calc.a $(CHECK_FLAGS) -L. -ls21_smart_calc

all: clean s21_smart_calc.a

install:
	@echo "Installing SmartCalc..."
	@echo "++++++++++++++++++++++++++++++++++++++++++"
	

clean:
	rm -rf *.o, *.g* *.info *.out report *.a *.dSYM

re: clean all

s21_smart_calc.o:
	$(CC) $(CC_FLAGS) -c *.c

s21_smart_calc.a: s21_smart_calc.o
	ar rcs libs21_smart_calc.a *.o
	rm -rf *.o
	ranlib libs21_smart_calc.a
	cp libs21_smart_calc.a s21_smart_calc.a

test: s21_smart_calc.a
	$(TEST_COMPILE)
	./a.out

gcov_report: s21_smart_calc.a test
	rm -f *.g*
	$(CC) $(CC_FLAGS) tests/*.c *.c libs21_smart_calc.a $(CHECK_FLAGS) $(GCOV_FLAGS)
	./a.out
	lcov -t a.out -o rep.info -c -d .
	genhtml -o report rep.info
	open ./report/index.html
	rm -rf *.gcda *.gcno

check:
	clang-format -style=google -i s21_*.c *.h
	make test
ifeq ($(OS), Darwin)
	CK_FORK=no leaks --atExit -- ./a.out
else
	valgrind ./a.out --leak-check=full
endif
	make clean

.PHONY: all clean re s21_smart_calc.a test gcov_report check
