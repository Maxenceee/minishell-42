MANDATORY_DIR	=	sources
OBJ_DIR			=	.objs

SRCS			=	$(MANDATORY_DIR)/utils/ft_isdigit.c \
					$(MANDATORY_DIR)/utils/ft_strtcpy.c \
					$(MANDATORY_DIR)/utils/ft_put_fd.c \
					$(MANDATORY_DIR)/utils/ft_contains.c \
					$(MANDATORY_DIR)/utils/ft_multichr.c \
					$(MANDATORY_DIR)/utils/ft_strlcpy.c \
					$(MANDATORY_DIR)/utils/ft_len.c \
					$(MANDATORY_DIR)/utils/ft_bzero.c \
					$(MANDATORY_DIR)/utils/ft_strjoin.c \
					$(MANDATORY_DIR)/utils/ft_isascii.c \
					$(MANDATORY_DIR)/utils/ft_memcpy.c \
					$(MANDATORY_DIR)/utils/ft_error.c \
					$(MANDATORY_DIR)/utils/ft_strequal.c \
					$(MANDATORY_DIR)/utils/ft_strjoin_char.c \
					$(MANDATORY_DIR)/utils/ft_split.c \
					$(MANDATORY_DIR)/utils/ft_isalpha.c \
					$(MANDATORY_DIR)/utils/ft_strtrim.c \
					$(MANDATORY_DIR)/utils/ft_replace.c \
					$(MANDATORY_DIR)/utils/ft_memmove.c \
					$(MANDATORY_DIR)/utils/ft_read_file.c \
					$(MANDATORY_DIR)/utils/ft_minmax.c \
					$(MANDATORY_DIR)/utils/ft_split_utils.c \
					$(MANDATORY_DIR)/utils/ft_calloc.c \
					$(MANDATORY_DIR)/utils/ft_strdup.c \
					$(MANDATORY_DIR)/utils/ft_ljoin.c \
					$(MANDATORY_DIR)/utils/ft_atoi.c \
					$(MANDATORY_DIR)/utils/ft_isalnum.c \
					$(MANDATORY_DIR)/utils/ft_itoa.c \
					$(MANDATORY_DIR)/utils/ft_strcmp.c \
					$(MANDATORY_DIR)/builtins/exit.c \
					$(MANDATORY_DIR)/builtins/unset.c \
					$(MANDATORY_DIR)/builtins/env.c \
					$(MANDATORY_DIR)/builtins/pwd.c \
					$(MANDATORY_DIR)/builtins/cd.c \
					$(MANDATORY_DIR)/builtins/export/print.c \
					$(MANDATORY_DIR)/builtins/export/export.c \
					$(MANDATORY_DIR)/builtins/echo.c \
					$(MANDATORY_DIR)/env/get_env_variable.c \
					$(MANDATORY_DIR)/env/push_env_element.c \
					$(MANDATORY_DIR)/env/free_env.c \
					$(MANDATORY_DIR)/env/parse_env.c \
					$(MANDATORY_DIR)/env/print_env.c \
					$(MANDATORY_DIR)/env/exit_status.c \
					$(MANDATORY_DIR)/env/parse_path.c \
					$(MANDATORY_DIR)/env/destroy_env_element.c \
					$(MANDATORY_DIR)/exec/builtins.c \
					$(MANDATORY_DIR)/exec/process.c \
					$(MANDATORY_DIR)/exec/pipes.c \
					$(MANDATORY_DIR)/exec/here_doc.c \
					$(MANDATORY_DIR)/exec/wait.c \
					$(MANDATORY_DIR)/exec/commands.c \
					$(MANDATORY_DIR)/exec/check_cmd.c \
					$(MANDATORY_DIR)/parsing/parsing_utils.c \
					$(MANDATORY_DIR)/parsing/ft_pipe_split.c \
					$(MANDATORY_DIR)/parsing/parse_expands.c \
					$(MANDATORY_DIR)/parsing/ft_split_cmd.c \
					$(MANDATORY_DIR)/parsing/free_parsing_cmd.c \
					$(MANDATORY_DIR)/parsing/parsing_cmd.c \
					$(MANDATORY_DIR)/main/signal_exit.c \
					$(MANDATORY_DIR)/main/mainloop.c \
					$(MANDATORY_DIR)/main/signals.c \
					$(MANDATORY_DIR)/main/minishell.c \
					$(MANDATORY_DIR)/exits/exit_with_code.c \
					$(MANDATORY_DIR)/exits/freeing.c

OBJS			=	$(patsubst $(MANDATORY_DIR)%.c, $(OBJ_DIR)%.o, $(SRCS))

HEADERS_DIR		=	includes
HEADERS			=	includes/pcolors.h \
					includes/minishell.h
HEADERS_SOURCES	=	$(MANDATORY_DIR)/utils/utils.h \
					$(MANDATORY_DIR)/builtins/builtins.h \
					$(MANDATORY_DIR)/env/env.h \
					$(MANDATORY_DIR)/exec/exec.h \
					$(MANDATORY_DIR)/parsing/parsing.h

ifeq ($(shell uname), Darwin)
READLINE_DIR	=	$(shell brew --prefix readline)
endif
READLINE_LIB	=	-lreadline -lhistory -L $(READLINE_DIR)/lib

CC				=	cc
RM				=	rm -f
CFLAGS			=	-I$(HEADERS_DIR) -I$(READLINE_DIR)/include -Wall -Wextra -Werror

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
	@$(CC) $(CFLAGS) -c $< -o $@ -g3
	@printf ${UP}${CUT}

all: $(NAME)

$(NAME): $(OBJS)
	@$(CC) $(OBJS) -o $(NAME) -lm $(READLINE_LIB) -g3
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
