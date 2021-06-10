SRCS = main.c routine.c utils.c write.c
OBJS = $(SRCS:.c=.o)
CFLAGS = -Wall -Wextra -Werror -g
CC = gcc
NAME = philo

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)
fclean: clean
	rm -f $(NAME)
re: fclean all