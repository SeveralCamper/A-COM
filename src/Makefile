CC = g++ -std=c++17

all: clean start

start:
	g++ simple_fractions/*.cc matrix_fraction/*.cc main.cc $(CFLAGS) -lm -o SLAE
	./SLAE

course:
	g++ simple_fractions/*.cc matrix_fraction/*.cc course_work_Alkhimovich/main.cc $(CFLAGS) -lm -o SLAE_course
	./SLAE_course

clean:
	rm -rf SLAE SLAE_course