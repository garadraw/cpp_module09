NAME = PmergeMe

CC = c++
CFLAGS = -Wall -Werror -Wextra -fsanitize=address -std=c++98
SRC = main.cpp \
		PmergeMe.cpp

RM = rm -f
.PHONY = all clean re

all: $(NAME)

$(NAME): $(SRC)
		$(CC) $(CFLAGS) $(SRC) -o $@

clean:
		$(RM) $(NAME)

fclean: clean

re: clean all