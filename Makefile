MANDATORY_DIR	=	sources
OBJ_DIR			=	.objs

SRCS			=	$(shell find $(MANDATORY_DIR) -name "*.c")
OBJS			=	$(patsubst $(MANDATORY_DIR)%.c, $(OBJ_DIR)%.o, $(SRCS))

HEADERS_DIR		=	includes
HEADERS_FONT_DIR =	$(MANDATORY_DIR)/font
HEADERS			=	$(shell find $(HEADERS_DIR) -name "*.h")
HEADERS_SOURCES	=	$(shell find $(MANDATORY_DIR) -name "*.h")

ifeq ($(shell uname), Darwin)
READLINE_DIR	=	$(shell brew --prefix readline)
endif
READLINE_LIB	=	-lreadline -lhistory -L $(READLINE_DIR)/lib

CC				=	cc
RM				=	rm -f
CFLAGS			=	-I$(HEADERS_DIR) -I$(HEADERS_FONT_DIR) -I$(READLINE_DIR)/include -g #-o3 -Wall -Wextra -Werror

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

re:				fclean all

.PHONY:			all clean fclean re
