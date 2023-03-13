CC = g++ -std=c++17

all: clean start

start:
	g++ simple_fractions/*.cc matrix_fraction/*.cc main.cc $(CFLAGS) -lm -o SLAE
	./SLAE

clean:
	rm -rf SLAE