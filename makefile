CC = g++
CFLAGS = -Wall -Wextra -g

SOURCES = main.cpp scanner.cpp parser.cpp interpreter.cpp
 
all: statement

statement:	
	$(CC) $(SOURCES) $(CFLAGS) -o statement.exe
	
run:
	./statement

clean:
	del statement.exe
