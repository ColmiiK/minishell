#Variables

NAME = minishell
INCLUDE = include
LIBFT = lib/libft
SRC_DIR = src/
OBJ_DIR = obj/
CC = gcc
CFLAGS = -Wall -Werror -Wextra -g
AR = ar rcs

# Colors

DEF_COLOR = $(shell tput sgr0)
GRAY = $(shell tput setaf 0)
RED = $(shell tput setaf 1)
GREEN = $(shell tput setaf 2)
YELLOW = $(shell tput setaf 3)
BLUE = $(shell tput setaf 4)
MAGENTA = $(shell tput setaf 5)
CYAN = $(shell tput setaf 6)
WHITE = $(shell tput setaf 7)

#Sources
	
SRC_FILES = main cleanup signal \
			parse/loop \
			parse/expansion \
			parse/heredoc_main \
			parse/heredoc_sub \
			parse/redirections \
			parse/setup_nodes \
			# builtin/cd \
			# builtin/echo \
			# builtin/env \
			# builtin/export \
			# builtin/pwd \
			# builtin/unset \
			# builtin/get_cmd \
			# builtin/utils \

SRC = $(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_FILES)))
OBJ = $(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC_FILES)))
OBJF = .cache_exists

###

all:		$(NAME)

$(NAME):	$(OBJ)
			@make -C $(LIBFT)
			@$(CC) -lreadline -I./$(INCLUDE) $(CFLAGS) $(OBJ) -L$(LIBFT) -lft -o $(NAME)
			@echo "$(GREEN)$(NAME) compiled!$(DEF_COLOR)"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c | $(OBJF)
			@mkdir -p $(dir $@)
			@echo "$(YELLOW)Compiling: $< $(DEF_COLOR)"
			@$(CC) -I./$(INCLUDE) $(CFLAGS) -c $< -o $@

$(OBJF):
			@mkdir -p $(OBJ_DIR)

clean:
			@rm -rf $(OBJ_DIR)
			@make clean -C $(LIBFT)
			@echo "$(BLUE)$(NAME) object files cleaned!$(DEF_COLOR)"

fclean:		
			@rm -rf $(OBJ_DIR)
			@rm -f $(NAME)
			@rm -rf $(NAME).dSYM
			@make fclean -C $(LIBFT)
			@echo "$(BLUE)$(NAME) executable cleaned!$(DEF_COLOR)"

re:			fclean all
			@echo "$(MAGENTA)$(NAME) recompiled!$(DEF_COLOR)"

norm:
			@norminette $(SRC) $(INCLUDE) $(LIBFT)

test:
			@make && ./valgrind.sh

.PHONY: all clean fclean re norm