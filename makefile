CC = gcc
CFLAGS = -Wall -Wextra -g
TARGET = main
SRCS = main.c func.c massive.c
OBJS = $(SRCS:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

main.o: main.c func.h massive.h
func.o: func.c func.h
massive.o: massive.c massive.h

clean:
	rm -f $(OBJS) $(TARGET)

rebuild: clean all

.PHONY: all clean rebuild