CC = g++ -std=c++17
CFLAGS = -Wall -Wextra

all: clean start

start:
	g++ simple_fractions/*.cc  matrix/*.cc matrix_fraction/*.cc main.cc $(CFLAGS) -lm -o SLAE
	./SLAE

clean:
	rm -rf SLAE