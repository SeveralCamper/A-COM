CC = g++ -std=c++17

all: clean run

run:
	g++ simple_fractions/*.cc main.cc -lm -o ZLP_course
	./ZLP_course

clang-format:
	clang-format -i  simple_fractions/* main.cc
	clang-format -n simple_fractions/* main.cc

clean:
	rm -rf ZLP_course