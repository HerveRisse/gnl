NAME = get_next_line.a
TEST_NAME = test_gnl

CC = cc
CFLAGS = -Wall -Wextra -Werror
BUFFER_SIZE ?= 42

SRCS = get_next_line.c get_next_line_utils.c
TEST_SRCS = main.c $(SRCS)

OBJS = $(SRCS:.c=.o)
TEST_OBJS = $(TEST_SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

test: fclean $(TEST_NAME)
	valgrind --leak-check=full ./$(TEST_NAME)

$(TEST_NAME): $(TEST_SRCS)
	$(CC) $(CFLAGS) -D BUFFER_SIZE=$(BUFFER_SIZE) $(TEST_SRCS) -o $(TEST_NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(TEST_OBJS)

fclean: clean
	rm -f $(NAME) $(TEST_NAME)

re: fclean all

.PHONY: all clean fclean re test
