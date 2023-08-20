CXX = g++
CPP_STD:=-std=c++17
TARGET:=s21_containers.a
CXXFLAGS = -g -Wall -Wextra # -Werror 
BUILD_DIR := build
SRC_DIRS := src
SRCS := $(shell find $(SRC_DIRS) -maxdepth 1 -name *.cc)
OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)
GT_SRCS := $(shell find $(SRC_DIRS)/Google_tests -maxdepth 1 -name *.cc)
GT_OBJS := $(GT_SRCS:%=$(BUILD_DIR)/%.o)
GT_FLAGS = -lgtest

OS := $(shell uname -s)

all: test

#  Google tests
test: $(GT_OBJS)
	$(CXX) $(CXXFLAGS) $(GT_OBJS) -o $(BUILD_DIR)/test.out $(GT_FLAGS)
	./$(BUILD_DIR)/test.out

# Build step for C++ source
$(BUILD_DIR)/%.cc.o: %.cc
	mkdir -p $(dir $@)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR)/*

clang:
	clang-format -n src/*.h src/Google_tests/*.cc
	clang-format -i src/*.h src/Google_tests/*.cc

start:
	./$(BUILD_DIR)/test.out

valgrind:
ifeq ($(OS), Darwin)
	echo $(OS)
	echo "For Aple --------------------"
	leaks -atExit -- ./build/test.out
else
	echo $(OS)
	echo "For Ubuntu --------------------"
	CK_FORK=no valgrind --vgdb=no --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=RESULT_VALGRIND.txt build/test.out
	grep errors RESULT_VALGRIND.txt
endif
	

t: clean clang test valgrind


# gcov_report: s21_containers_tests.o
# ifeq ($(OS), Linux)
# 	echo $(OS2)
# ifeq ($(OS2), ID=alpine)
# 	echo "For Alpine --------------------"
# 	$(CC) $(CFLAGS) s21_containers_tests.o s21_vector.cc -o test.out $(GFLAGS)
# else
# 	echo "For Ubuntu --------------------"
# 	$(CC) $(CFLAGS) s21_containers_tests.o s21_vector.cc -o test.out $(GFLAGS)
# endif
# else
# 	echo "For Apple --------------------"
# 	$(CC) $(CFLAGS) s21_containers_tests.o s21_vector.cc -o test.out -lgtest -lm --coverage
# endif
# 	./test.out
# 	lcov -t "test" -o test.info -c -d .
# 	genhtml -o report test.info
# 	open report/index.html

