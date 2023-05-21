CC = g++ -std=c++17

all: clean start

start:
	g++ simple_fractions/*.cc matrix_fraction/*.cc main.cc $(CFLAGS) -lm -o SLAE
	./SLAE

course:
	g++ simple_fractions/*.cc matrix_fraction/*.cc course_work_Alkhimovich/main.cc $(CFLAGS) -lm -o SLAE_course
	./SLAE_course

clang-format:
	clang-format -i  simple_fractions/* matrix_fraction/* main.cc
	clang-format -n simple_fractions/* matrix_fraction/* main.cc

clean:
	rm -rf SLAE SLAE_course

