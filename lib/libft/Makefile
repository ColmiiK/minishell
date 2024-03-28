#Variables

NAME = libft.a
INCLUDE = ../../include
SRC_DIR = src/
OBJ_DIR = obj/
CC = gcc
CFLAGS = -Wall -Werror -Wextra
RM = rm -f
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
	
SRC_FILES = ft_isalpha ft_isdigit ft_isalnum ft_isascii ft_isprint \
	ft_strlen ft_memset ft_bzero ft_memcpy ft_memcpy ft_memmove \
	ft_strlcpy ft_strlcat ft_toupper ft_tolower ft_strchr \
	ft_strrchr ft_strncmp ft_memchr ft_memcmp ft_strnstr ft_atoi \
	ft_calloc ft_strdup ft_substr ft_strjoin ft_strtrim ft_split \
	ft_itoa ft_strmapi ft_striteri ft_putchar_fd ft_putstr_fd \
	ft_putendl_fd ft_putnbr_fd get_next_line ft_printf print_characters \
	print_hexes print_numbers ft_realloc ft_strtok ft_strjoin_ex \
	ft_double_ptr_amount
	
B_SRC_FILES = ft_lstnew_bonus ft_lstadd_front_bonus ft_lstsize_bonus ft_lstlast_bonus ft_lstadd_back_bonus \
	ft_lstdelone_bonus ft_lstclear_bonus ft_lstiter_bonus ft_lstmap_bonus

SRC = $(addprefix $(SRC_DIR), $(addsuffix .c, $(SRC_FILES)))
B_SRC = $(addprefix $(SRC_DIR), $(addsuffix .c, $(B_SRC_FILES)))
OBJ = $(addprefix $(OBJ_DIR), $(addsuffix .o, $(SRC_FILES)))
B_OBJ = $(addprefix $(OBJ_DIR), $(addsuffix .o, $(B_SRC_FILES)))
OBJF = .cache_exists

###

all:		$(NAME)

$(NAME):	$(OBJ)
			@ar -rc $@ $?
			@echo "$(GREEN)$(NAME) compiled!$(DEF_COLOR)"

$(OBJ_DIR)%.o: $(SRC_DIR)%.c | $(OBJF)
			@echo "$(YELLOW)Compiling: $< $(DEF_COLOR)"
			@$(CC) -I./$(INCLUDE) $(CFLAGS) -c $< -o $@

$(OBJ_DIR)%.o: $(B_SRC_DIR)%.c | $(OBJF)
			@echo "$(YELLOW)Compiling: $< $(DEF_COLOR)"
			@$(CC) -I./$(INCLUDE) $(CFLAGS) -c $< -o $@

$(OBJF):
			@mkdir -p $(OBJ_DIR)

clean:
			@$(RM) -rf $(OBJ_DIR)
			@echo "$(CYAN)$(NAME) object files cleaned!$(DEF_COLOR)"

fclean:		
			@$(RM) -rf $(OBJ_DIR)
			@$(RM) -f $(NAME)
			@echo "$(BLUE)$(NAME) executable cleaned!$(DEF_COLOR)"

re:			fclean all
			@echo "$(MAGENTA)$(NAME) recompiled!$(DEF_COLOR)"

norm:
			@norminette $(SRC) $(B_SRC) $(INCLUDE)

.PHONY: all clean fclean re norm