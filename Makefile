CPPFLAGS= -std=c++17
CC=clang++

all: simulator

simulator: main.o main.cpp Bank.h Store.h Event.h simUtils.h
	$(CC) $(CPPFLAGS) -o runSim main.o

test:
	chmod +x test.sh
	./test.sh
