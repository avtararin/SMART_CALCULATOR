TARGET = Calculator_v1.0
NAME = s21_smart_calc
CC = gcc
CC_FLAGS =  -Wall -Wextra -Werror -g #-pedantic
GCOV_FLAGS = -L. -ls21_smart_calc --coverage
OS = $(shell uname)
ifeq ($(OS), Linux)
	CHECK_FLAGS = -lcheck -pthread -lrt -lm -lsubunit
else
	CHECK_FLAGS = $(shell pkg-config --libs --cflags check) -lm
endif

TEST_COMPILE = $(CC) $(CC_FLAGS) Backend/tests/*.c libs21_smart_calc.a $(CHECK_FLAGS) -L. -ls21_smart_calc

all: clean s21_smart_calc.a


install:       
	echo "Installation of $(TARGET).app:"
	mkdir -p ../build
	cd ./Frontend1 && qmake && make && make clean && rm -rf Makefile && mv Frontend1 ../../build/$(TARGET).app
	echo "Installation completed! You can find app in the ../build/ folder!"

uninstall:
	rm -rf ../build
	echo "Uninstall completed!"

clean:
	rm -rf *.o, *.g* *.info *.out report *.a *.dSYM
	rm -rf *.o
	cd ./Backend && rm -rf *.o, *.g* *.info *.out report *.a *.dSYM
	cd ./Frontend1 && rm -rf *.o, *.g* *.info *.out report *.a *.dSYM *.stash

re: clean all

dist: install
	mkdir -p ../dist
	@cp -R ../build/$(TARGET).app ../dist
	@cp -R . ../dist/src
	@cd ../dist && tar cvzf $(TARGET).tgz *
	@cd ../dist && rm -rf $(TARGET).app
	@rm -rf ../dist/src
	echo "Archive creation completed successfully!"

dvi:
	doxygen
	open doxygen/html/index.html

s21_smart_calc.o:
	$(CC) $(CC_FLAGS) -c Backend/*.c

s21_smart_calc.a: s21_smart_calc.o
	ar rcs libs21_smart_calc.a *.o
	rm -rf *.o
	ranlib libs21_smart_calc.a
	cp libs21_smart_calc.a s21_smart_calc.a

test: s21_smart_calc.a
	$(TEST_COMPILE)
	./a.out

gcov_report: s21_smart_calc.a test
	rm -f Backend/*.g*
	$(CC) $(CC_FLAGS) Backend/tests/*.c  Backend/*.c libs21_smart_calc.a $(CHECK_FLAGS) $(GCOV_FLAGS)
	./a.out
	lcov -t a.out -o rep.info -c -d .
	genhtml -o report rep.info
	open ./report/index.html
	rm -rf *.gcda *.gcno

check:
	clang-format -i Backend/*.h
	clang-format -i Backend/*.h
	make test
ifeq ($(OS), Darwin)
	CK_FORK=no leaks --atExit -- Backend/./a.out
else
	valgrind ./a.out --leak-check=full
endif
	make clean

.PHONY: all clean re s21_smart_calc.a test gcov_report check
