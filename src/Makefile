WWW = -std=c++17 -Wall -Werror -Wextra -lstdc++
LINUX=-lsubunit -lrt -lpthread -lm
LFLAGS=-fprofile-arcs -ftest-coverage
LIBS=-lgtest -lgmock -pthread
OS=$(shell uname -s)

all: clean test

rebuild: clean all 

test: clean s21_matrix_oop.a
ifeq ($(OS), Darwin)
	gcc $(WWW) test.cpp s21_matrix_oop.a -o test $(LIBS)
else
	gcc $(WWW) test.cpp s21_matrix_oop.a -o test $(LIBS) $(LINUX)
endif
	./test

gcov_report: clean_test
ifeq ($(OS), Darwin)
	gcc $(WWW) --coverage test.cpp s21_matrix_oop.cpp -o test $(LIBS)
else
	gcc $(WWW) --coverage test.cpp s21_matrix_oop.cpp -o test $(LIBS) $(LINUX)
endif
	./test
	lcov -t "test" -o test.info --no-external -c -d .
	genhtml -o report test.info
	open report/index.html

s21_matrix_oop.a: build_s21_matrix_oop

build_s21_matrix_oop:
	gcc -c s21_*.cpp
	ar rcs s21_matrix_oop.a s21_*.o
	ranlib s21_matrix_oop.a


cppcheck:
	cppcheck --enable=all --suppress=missingIncludeSystem *.cpp

cpplint:
	cp ../materials/linters/CPPLINT.cfg .
	python3 ../materials/linters/cpplint.py --extensions=cpp *.h
	python3 ../materials/linters/cpplint.py --extensions=cpp *.cpp
	rm -rf CPPLINT.cfg


install_brew:
	cd ~
	curl -fsSL https://rawgit.com/kube/42homebrew/master/install.sh | zsh
	brew install lcov

install_valgrind:
	brew install --HEAD LouisBrunner/valgrind/valgrind

install_cpch:
	brew install cppcheck

git: clean
	git add .
	git commit -m'finish'
	git push origin develop

clean_obj:
	rm -rf *.o

clean_lib: 
	rm -rf *.a

clean_test:
	rm -rf *.gcda
	rm -rf *.gcno
	rm -rf *.info
	rm -rf test
	rm -rf report

clean: clean_lib clean_test clean_obj
