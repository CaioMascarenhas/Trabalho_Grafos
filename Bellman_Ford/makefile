CC = g++
CFLAGS = -std=c++11

all: bellman_ford.bin

bellman_ford.bin: bellman_ford.cpp
	$(CC) $(CFLAGS) bellman_ford.cpp -o bellman_ford.bin

clean:
	rm -f bellman_ford.bin