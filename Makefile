NAME = a.out
SRCS = main.c \
	   minishell_utils.c \
	   minishell_env.c \
	   minishell_argc_argv.c \
	   minishell_path.c \
	   minishell_command.c \
	   minishell_construction.c \
	   minishell_len_construction.c \
	   minishell_len_utils.c \
	   minishell_list_utils.c \
	   minishell_fill_list.c
OBJS = $(SRCS:%.c=%.o)
CC = cc
CFLAGS = -Wall -Werror -Wextra
LIBFT = ./libft
LIBFT_A = $(LIBFT)/libft.a
LIBS = -lreadline -L$(LIBFT) -lft
HEADER = minishell.h

all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJS) $(HEADER) $(LIBFT_A)
	$(CC) $(CFLAGS) $(OBJS) $(LIBS) -o $(NAME)

$(LIBFT_A):
	@make -C $(LIBFT) bonus

clean:
	rm -f $(OBJS)
	@make -C $(LIBFT) clean

fclean: clean
	rm -f $(NAME)
	@make -C $(LIBFT) fclean

re: fclean all

.PHONY: all clean fclean re
