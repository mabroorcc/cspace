CC = gcc
CFLAGS = -Wall -Wextra -I/opt/local/include
LDFLAGS = -L/opt/local/lib
LDLIBS = -lpng -lm

SRCS = main.c
OBJS = $(SRCS:.c=.o)
TARGET = my_program

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(LDFLAGS) $(OBJS) $(LDLIBS) -o $(TARGET)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET) && rm -rf my_program main.o

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all run clean