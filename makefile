CC = g++
CFLAGS = -Wall -Wextra -g

SOURCES = $(wildcard *.cpp)
OBJS=$(SOURCES:.cpp=.o)

all: statement  

statement: $(OBJS)	
	$(CC) $(OBJS) $(CFLAGS) -o statement.exe
	
run:
	./statement

clean:
	del $(OBJS)
	del statement.exe
