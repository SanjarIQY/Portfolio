CC = gcc
CFLAGS = -g -Wall -Wextra -Werror
SOURCES = ls.c
TARGET = my_ls

$(TARGET):$(SOURCES)
	$(CC) $(CFLAGS) -o $@ $^

.PHONY: fclean

fclean:
	@rm -r $(TARGET)