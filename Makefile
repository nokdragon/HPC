CC = gcc
CFLAGS = -Wall -O0 -O3 -fstrict-aliasing -msse4.2 -fopenmp -std=gnu99
LDFLAGS=-lgomp
EXEC_NAME = exec
INCLUDES =
LIBS =
FILES =  $(wildcard *.c)
OBJ_FILES = $(FILES:.c=.o)
INSTALL_DIR = /usr/bin

all : $(EXEC_NAME)

clean :
	rm -rf $(EXEC_NAME) $(OBJ_FILES) .depends *~ *#
	rm -rf hall_FD/*
	rm -rf hall_SD/*
	rm -rf $(EXEC_NAME).exe

$(EXEC_NAME) : $(OBJ_FILES) $(FILES)
	$(CC) -o $(EXEC_NAME) $(OBJ_FILES) $(LIBS) $(LDFLAGS)

%.o: %.cc
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ -c $<

%.o: %.c
	gcc $(CFLAGS) $(INCLUDES) -o $@ -c $<

.depends:
	$(CC) -MM $(FILES) > .depends

-include .depends
