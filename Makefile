CXX = g++
CPP_STD:=-std=c++17
TARGET:=s21_containers.a
CXXFLAGS = -g -Werror -Wall -Wextra
BUILD_DIR := build
SRC_DIRS := src
SRCS := $(shell find $(SRC_DIRS) -maxdepth 1 -name *.cc)
OBJS := $(SRCS:%=$(BUILD_DIR)/%.o)
GT_SRCS := $(shell find $(SRC_DIRS)/Google_tests -maxdepth 1 -name *.cc)
GT_OBJS := $(GT_SRCS:%=$(BUILD_DIR)/%.o)
GT_FLAGS = -lgtest -lpthread

OS := $(shell uname -s)
OS2 := $(shell cat /etc/*-release | grep ID=a)

all: s21_containers.a

test: s21_containers.a $(GT_OBJS)
	$(CXX) $(CFLAGS) $(GT_OBJS) $(BUILD_DIR)/$(TARGET) -o $(BUILD_DIR)/test.out $(GT_FLAGS)
	./$(BUILD_DIR)/test.out

clean:
	rm -r $(BUILD_DIR)

clang:
	clang-format -n src/*.cc src/*.h
	clang-format -i src/*.cc src/*.h

start:
	./build/final_program

valgrind:
	CK_FORK=no valgrind --vgdb=no --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose --log-file=RESULT_VALGRIND.txt $(BUILD_DIR)/test.out
	cat RESULT_VALGRIND.txt

t: clang all start valgrind


# Final build
$(TARGET): $(OBJS)
	ar -rc $(BUILD_DIR)/$(TARGET) $(OBJS)
	ranlib $(BUILD_DIR)/$(TARGET)

# Build step for C++ source
$(BUILD_DIR)/%.cc.o: %.cc
	mkdir -p $(dir $@)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

# test: s21_containers.a s21_containers_tests.o
# ifeq ($(OS), Linux)
# 	echo $(OS2)
# ifeq ($(OS2), ID=alpine)
# 	echo "For Alpine --------------------"
# 	$(CC) $(CFLAGS) s21_containers_tests.o s21_containers.a -o test.out $(LINFLAGS)
# else
# 	echo "For Ubuntu --------------------"
# 	$(CC) $(CFLAGS) s21_containers_tests.o s21_containers.a -o test.out $(LINFLAGS)
# endif
# else
# 	echo "For Apple --------------------"
# 	$(CC) $(CFLAGS) s21_containers_tests.o s21_containers.a -o test.out -lgtest -lm
# endif
# 	./test.out

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

# s21_containers.a: s21_containers.o
# 	ar -rc ./s21_containers.a s21_containers.o
# 	ranlib ./s21_containers.a
