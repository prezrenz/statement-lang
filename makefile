CC = g++
CFLAGS = -Wall -Wextra -g

SOURCES = main.cpp scanner.cpp parser.cpp
 
all: statement

statement:	
	$(CC) $(SOURCES) $(CFLAGS) -o statement.exe
	
run:
	./statement

clean:
	del statement.exe
