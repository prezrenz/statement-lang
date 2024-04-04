CC = g++
CFLAGS = -Wall -Wextra -g

SOURCES = main.cpp

all: statement  

statement:	
	$(CC) $(SOURCES) $(CFLAGS) -o statement.exe
	
run:
	./statement

clean:
	del main.o
	del statement.exe
