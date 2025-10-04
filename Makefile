NAME := philo

SRCS := check_args.c \
		init.c \
		print.c \
		routine.c \
		monitoring.c \
		utils.c \
		single_philo.c \
		main.c

OBJS := $(SRCS:%.c=%.o)

HEADERS := philosophers.h

CFLAGS = -Wall -Wextra -Werror

$(NAME) : $(OBJS)
	cc $(CFLAGS) -o $@ $^

%.o: %.c $(HEADERS)
	cc -c $< -o $@ $(CFLAGS)

all: $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all
