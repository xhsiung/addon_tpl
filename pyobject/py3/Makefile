CC=gcc
CXX=g++
CFLAGS=-L.
LIBS=-shared -fPIC
INCLUDE=-I/usr/include/python3.5m -I.

SOURCES=addon.c
OBJS=$(SOURCES:.c=.o)

OUT=addon.so

all:task main

main:$(OBJS)
	$(CC) -o $(OUT) $^ $(CFLAGS) $(LIBS) $(INCLUDE) 

%.o:%.c
	$(CC) -c $< $(CFLAGS) $(LIBS) $(INCLUDE) 

%.o:%.cpp
	$(CC) -c $< $(CFLAGS) $(LIBS) $(INCLUDE) 

task:
	@echo $(OBJS)

test:
	python3  test.py

clean:
	rm -rf *.o 
