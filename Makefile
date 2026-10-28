CC ?= gcc
CFLAGS = -Wall -Wextra -std=c99 -g
TARGET = source2html
SRCS = main.c parser.c html.c keyword.c s_html.c evaluation.c
OBJS = $(SRCS:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJS)

%.o: %.c header.h html.h keyword.h s_html.h
	$(CC) $(CFLAGS) -c $< -o $@

run: $(TARGET)
	./$(TARGET) input_file.c output.html

clean:
	rm -f $(OBJS) $(TARGET) $(TARGET).exe output.html

.PHONY: all run clean
