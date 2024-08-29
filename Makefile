NAME = minishell

SRC        :=      src/EXPANDER/clearemptylextables.c \
                          src/EXPANDER/cmdexpander.c \
                          src/EXPANDER/dollarexpander.c \
                          src/EXPANDER/expander.c \
                          src/LEXER/addlexnode.c \
                          src/LEXER/checksyntax.c \
                          src/LEXER/getarg.c \
                          src/LEXER/lexer.c \
                          src/LEXER/setlextypes.c \
						  src/LEXER/printlexer.c \
                          src/LIBFT/ft_itoa.c \
                          src/LIBFT/ft_memcpy.c \
                          src/LIBFT/ft_strcmp.c \
                          src/LIBFT/ft_strdup.c \
                          src/LIBFT/ft_strjoin.c \
                          src/LIBFT/ft_strlcpy.c \
                          src/LIBFT/ft_strlen.c \
						  src/LIBFT/ft_putstr_fd.c \
                          src/MAIN/init.c \
                          src/MAIN/main.c \
                          src/MAIN/signal.c \
                          src/PARSER/createfilelist.c \
                          src/PARSER/fillcmdtable.c \
                          src/PARSER/parser.c \
                          src/STRING/strappendchar.c \
                          src/STRING/trimleft.c \
                          src/UTILS/error.c \
                          src/UTILS/ismetachar.c \

CFLAGS = -Wall -Wextra -Werror -g #-fsanitize=address # MallocStackLogging=1
READLINE = lib/readline/lib/libreadline.a

RM = @rm -rf
CC = @cc

OBJS = $(SRC:.c=.o)

RESET = \033[0m
BOLD = \033[1m
YELLOW = \033[33m
GREEN = \033[32m
RED = \033[31m

all: $(READLINE) $(NAME)

$(READLINE):
	@echo "$(BOLD)$(YELLOW)[DOWNLOADING READLINE...]$(RESET)"
	@curl -O https://ftp.gnu.org/gnu/readline/readline-8.2.tar.gz
	@tar -xvf readline-8.2.tar.gz
	@$(RM) readline-8.2.tar.gz
	@cd readline-8.2 && ./configure --prefix=${PWD}/lib/readline
	@cd readline-8.2 && make install
	@$(RM) readline-8.2

$(NAME): $(OBJS)
	@echo "$(BOLD)$(YELLOW)[COMPILING...]$(RESET)"
	@sleep 0.5
	@$(CC) -o $(NAME) $(OBJS) $(CFLAGS) -I${PWD}/lib/readline/include/ -lreadline -L${PWD}/lib/readline/lib
	@clear
	@echo "$(BOLD)$(YELLOW)[COMPILATION COMPLETE]$(RESET)"

%.o: %.c
	@$(CC) $(CFLAGS) -c $< -o $@ -I${PWD}/lib/readline/include/

fclean: clean
	@echo "$(BOLD)$(RED)[DELETING...]$(RESET)"
	@sleep 0.5
	@$(RM) $(NAME)
	@echo "$(BOLD)$(RED)[ALL FİLE DELETED]$(RESET)"

clean:
	@echo "$(BOLD)$(YELLOW)[DELETING OBJECTS...]$(RESET)"
	@sleep 0.5
	@$(RM) $(OBJS)
	@echo "$(BOLD)$(RED)[ALL OBJECTS DELETED]$(RESET)"

re: fclean all

.PHONY: all fclean clean re