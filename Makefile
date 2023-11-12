MANDATORY_DIR	=	sources
OBJ_DIR			=	.objs

SRCS			=	sources/utils/ft_isdigit.c \
					sources/utils/ft_strtcpy.c \
					sources/utils/ft_put_fd.c \
					sources/utils/ft_contains.c \
					sources/utils/ft_multichr.c \
					sources/utils/ft_strlcpy.c \
					sources/utils/ft_len.c \
					sources/utils/ft_bzero.c \
					sources/utils/ft_strjoin.c \
					sources/utils/ft_isascii.c \
					sources/utils/ft_memcpy.c \
					sources/utils/ft_error.c \
					sources/utils/ft_strjoin_char.c \
					sources/utils/ft_split.c \
					sources/utils/ft_isalpha.c \
					sources/utils/ft_strtrim.c \
					sources/utils/ft_replace.c \
					sources/utils/ft_memmove.c \
					sources/utils/ft_read_file.c \
					sources/utils/ft_minmax.c \
					sources/utils/ft_split_utils.c \
					sources/utils/ft_calloc.c \
					sources/utils/ft_strdup.c \
					sources/utils/ft_ljoin.c \
					sources/utils/ft_atoi.c \
					sources/utils/ft_isalnum.c \
					sources/utils/ft_itoa.c \
					sources/utils/ft_strcmp.c \
					sources/builtins/exit.c \
					sources/builtins/unset.c \
					sources/builtins/env.c \
					sources/builtins/pwd.c \
					sources/builtins/cd.c \
					sources/builtins/export/print.c \
					sources/builtins/export/export.c \
					sources/builtins/echo.c \
					sources/env/get_env_variable.c \
					sources/env/push_env_element.c \
					sources/env/free_env.c \
					sources/env/parse_env.c \
					sources/env/print_env.c \
					sources/env/exit_status.c \
					sources/env/parse_path.c \
					sources/env/destroy_env_element.c \
					sources/exec/builtins.c \
					sources/exec/process.c \
					sources/exec/pipes.c \
					sources/exec/here_doc.c \
					sources/exec/wait.c \
					sources/exec/commands.c \
					sources/exec/check_cmd.c \
					sources/parsing/parsing_utils.c \
					sources/parsing/ft_pipe_split.c \
					sources/parsing/parse_expands.c \
					sources/parsing/ft_split_cmd.c \
					sources/parsing/free_parsing_cmd.c \
					sources/parsing/parsing_cmd.c \
					sources/main/signal_exit.c \
					sources/main/mainloop.c \
					sources/main/signals.c \
					sources/main/minishell.c \
					sources/exits/exit_with_code.c \
					sources/exits/freeing.c

OBJS			=	$(patsubst $(MANDATORY_DIR)%.c, $(OBJ_DIR)%.o, $(SRCS))

HEADERS_DIR		=	includes
HEADERS			=	includes/pcolors.h \
					includes/minishell.h
HEADERS_SOURCES	=	sources/utils/utils.h \
					sources/builtins/builtins.h \
					sources/env/env.h \
					sources/exec/exec.h \
					sources/parsing/parsing.h

ifeq ($(shell uname), Darwin)
READLINE_DIR	=	$(shell brew --prefix readline)
endif
READLINE_LIB	=	-lreadline -lhistory -L $(READLINE_DIR)/lib

CC				=	cc
RM				=	rm -f
CFLAGS			=	-I$(HEADERS_DIR) -I$(READLINE_DIR)/include -g -Wall -Wextra -Werror

NAME			=	minishell

GREEN			=	\033[1;32m
BLUE			=	\033[1;34m
RED				=	\033[1;31m
YELLOW      	=	\033[1;33m
DEFAULT			=	\033[0m
UP				=	"\033[A"
CUT				=	"\033[K"

$(OBJ_DIR)/%.o: $(MANDATORY_DIR)/%.c $(HEADERS) $(HEADERS_SOURCES) Makefile
	@mkdir -p $(@D)
	@echo "$(YELLOW)Compiling [$<]$(DEFAULT)"
	@$(CC) $(CFLAGS) -c $< -o $@
	@printf ${UP}${CUT}

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(OBJS) -o $(NAME) -lm -g $(READLINE_LIB)
	@echo "$(GREEN)$(NAME) compiled!$(DEFAULT)"

clean:
	@echo "$(RED)Cleaning build folder$(DEFAULT)"
	@$(RM) -r $(OBJ_DIR)

fclean: clean
	@echo "$(RED)Cleaning $(NAME)$(DEFAULT)"
	@$(RM) $(NAME)

leak: all
	valgrind --leak-check=full --suppressions=.local.supp \
	--show-leak-kinds=all --track-fds=yes --trace-children=yes ./$(NAME)

re:				fclean all

.PHONY:			all clean fclean re
