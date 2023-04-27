CC = gcc
FLAG_C = -c
CFLAGS = -Wall -Werror -Wextra -std=c11
SRC_C = s21_*.c
SRC_O = s21_*.o
SRC_COV = cov_*.o
GKOVFLAGS = -lgcov --coverage
TESTS_SOURSES = ./stringh.check
CHECKFLAGS = -lcheck
OS = $(shell uname)
ifeq ($(OS), Linux)
CHECKFLAGS += -lm -lpthread -lsubunit -lrt
endif

all: clean s21_string.a test clean

s21_string.a:
	$(CC) $(FLAG_C) $(CFLAGS) $(SRC_C)
	ar rc s21_string.a $(SRC_O)
	ranlib s21_string.a

test: clean s21_string.a
	checkmk clean_mode=1 stringh.check s21_string.h > test.c
	$(CC) test.c $(CHECKFLAGS) -lm -lcheck s21_string.a -o test
	./test

lib_cov.a: 
	$(CC) $(FLAG_C) $(CFLAGS) -g $(GKOVFLAGS) $(SRC_C)
	ar rc lib_cov.a $(SRC_O)
	ranlib lib_cov.a

gcov_report: clean $(TESTS_SOURSES) lib_cov.a
	checkmk clean_mode=1 stringh.check s21_string.h > test.c
	$(CC) test.c -c
	$(CC) test.o -g $(CHECKFLAGS) lib_cov.a -o test $(GKOVFLAGS)
	./test
	lcov -t "t" -o test.info -c -d .
	genhtml -o report test.info
	open ./report/index.html
	rm -f test.c

clean:
	rm -rf test.c *.o test
	rm -rf $(SRC_O) *.a
	rm -rf *.gcov *.gcda *.gcno *.out *.info *.txt

check:
	cppcheck --enable=all --suppress=missingIncludeSystem --inconclusive --check-config *.c *.h
	cp ../materials/linters/CPPLINT.cfg CPPLINT.cfg
	python3 ../materials/linters/cpplint.py --extensions=c *.c *.h
	rm CPPLINT.cfg
	clang-format -style=Google -n *.c *.h

leaks: test
	CK_FORK=no leaks --atExit -- ./test

valgrind: test
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=RESULT_VALGRIND.txt ./test
