# ======================================
# ChatIRC Makefile
# ======================================

CC = gcc

CFLAGS = -Wall -Wextra -Werror -g -Iinclude

TARGET = irc_client

SRC = \
	src/main.c \
	src/connect.c \
	src/irc.c \
	src/utils.c \
	src/cleanup.c

OBJ = $(SRC:.c=.o)

LIBS = -lpthread

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(OBJ) -o $(TARGET) $(LIBS)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(TARGET)

re: fclean all

.PHONY: all clean fclean re
