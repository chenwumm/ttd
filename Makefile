CC = gcc
CFLAGS = -Wall -Wextra -std=c99 -O2
LIBS = -lncursesw
SRCS = main.c cursor.c utils.c commands.c
OBJS = $(SRCS:.c=.o)
TARGET = ttd

.PHONY: all clean install uninstall

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)

install: $(TARGET)
	cp $(TARGET) /usr/local/bin/

uninstall:
	rm -f /usr/local/bin/$(TARGET)

# 此为iFlow AI CLI编写。
