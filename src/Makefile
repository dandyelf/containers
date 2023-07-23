CC = g++
CFLAGS = -g -Werror -Wall -Wextra
LINFLAGS = -lgtest -lrt -lpthread -lm
GFLAGS = -lgtest -lrt -lpthread -lm --coverage
OS := $(shell uname -s)
OS2 := $(shell cat /etc/*-release | grep ID=a)



all: s21_containers.a

test: s21_containers.a s21_containers_tests.o
ifeq ($(OS), Linux)
	echo $(OS2)
ifeq ($(OS2), ID=alpine)
	echo "For Alpine --------------------"
	$(CC) $(CFLAGS) s21_containers_tests.o s21_containers.a -o test.out $(LINFLAGS)
else
	echo "For Ubuntu --------------------"
	$(CC) $(CFLAGS) s21_containers_tests.o s21_containers.a -o test.out $(LINFLAGS)
endif
else
	echo "For Apple --------------------"
	$(CC) $(CFLAGS) s21_containers_tests.o s21_containers.a -o test.out -lgtest -lm
endif
	./test.out

gcov_report: s21_containers_tests.o
ifeq ($(OS), Linux)
	echo $(OS2)
ifeq ($(OS2), ID=alpine)
	echo "For Alpine --------------------"
	$(CC) $(CFLAGS) s21_containers_tests.o s21_vector.cc -o test.out $(GFLAGS)
else
	echo "For Ubuntu --------------------"
	$(CC) $(CFLAGS) s21_containers_tests.o s21_vector.cc -o test.out $(GFLAGS)
endif
else
	echo "For Apple --------------------"
	$(CC) $(CFLAGS) s21_containers_tests.o s21_vector.cc -o test.out -lgtest -lm --coverage
endif
	./test.out
	lcov -t "test" -o test.info -c -d .
	genhtml -o report test.info
	open report/index.html

s21_containers.a: s21_containers.o
	ar -rc ./s21_containers.a s21_containers.o
	ranlib ./s21_containers.a

s21_containers.o:
	$(CC) $(CFLAGS) -c s21_vector.cc -o s21_containers.o -lm

s21_containers_tests.o:
	$(CC) $(CFLAGS) -c ./Google_tests/s21_containers_tests.cc -lm

clean:
	rm -rf *.o test t *.gcda *.gcno *.info *.out s21_containers.a ./report/*