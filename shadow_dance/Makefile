# 多个 .c 一起交给 gcc，链接成一个程序。在本目录执行 make。
CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -Wpedantic -g
SRCS = main.c note.c lane.c enemy.c score.c
HEADERS = game.h note.h lane.h enemy.h score.h

.PHONY: all test clean

all: shadow_dance

shadow_dance: $(SRCS) $(HEADERS)
	$(CC) $(CFLAGS) -o shadow_dance $(SRCS) -lm

test: shadow_dance
	./shadow_dance --test

clean:
	rm -f shadow_dance
