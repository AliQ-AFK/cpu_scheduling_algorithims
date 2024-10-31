CC = gcc
CFLAGS = -Wall -Wextra -Werror -g -Iinclude

TARGET = cpu_scheduling

SRCS = $(wildcard src/*.c)
OBJS = $(SRCS:.c=.o)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

src/%.o: src/%.c include/utils.h
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TARGET)
