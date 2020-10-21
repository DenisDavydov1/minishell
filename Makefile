NAME = minishell

LIBFT_DIR = ./libft/
LIBFT = $(LIBFT_DIR)libft.a
LIBFT_HDR = $(LIBFT_DIR)libft.h
LIBFT_SRC_LIST = ft_memset.c ft_bzero.c ft_memcpy.c ft_memccpy.c ft_memmove.c \
ft_memchr.c ft_memcmp.c ft_strlen.c ft_strlcpy.c ft_strlcat.c ft_strchr.c \
ft_strrchr.c ft_strnstr.c ft_strncmp.c ft_atoi.c ft_isalpha.c ft_isdigit.c \
ft_isalnum.c ft_isascii.c ft_isprint.c ft_toupper.c ft_tolower.c \
ft_calloc.c ft_strdup.c ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c \
ft_itoa.c ft_strmapi.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c \
ft_putnbr_fd.c ft_strcmp.c ft_strpass.c ft_strcpy.c
#ft_splitset.c
LIBFT_SRC = $(addprefix $(LIBFT_DIR), $(LIBFT_SRC_LIST))
LIBFT_OBJ_LIST = $(patsubst %.c, %.o, $(LIBFT_SRC_LIST))
LIBFT_OBJ = $(addprefix $(LIBFT_DIR), $(LIBFT_OBJ_LIST))

HDR_DIR = ./#include/
HDR_LIST = minishell.h
HDR = $(addprefix $(HDR_DIR), $(HDR_LIST))

SRC_DIR = ./#src/
SRC_DIR_FUNCTION = function/
SRC_DIR_PARCER = parser/
SRC_DIR_UTILS = utils/
SRC_LIST = main.c parser.c function/cd.c function/exit.c \
function/env.c function/export.c function/echo.c function/pwd.c \
function/unset.c function/launch_function.c parser/parser_quotes.c utils/env_utils.c \
utils/errors.c utils/command_read.c utils/export_utils.c utils/signal_handler.c \
utils/init.c utils/utils.c

SRC = $(addprefix $(SRC_DIR), $(SRC_LIST))

OBJ_DIR = ./obj/
OBJ_LIST = $(patsubst %.c, $(OBJ_DIR)%.o, $(SRC_LIST))
#OBJ = $(addprefix $(OBJ_DIR), $(OBJ_LIST))

MAKE = make -sC
CC = gcc
FLAGS = #-Wall -Wextra -Werror
LIBS = -lft -L./libft
INCLUDE = -I$(HDR_DIR)

#.PHONY: all clean fclean re

all: $(NAME)

$(NAME): $(LIBFT) $(LIBFT_OBJ) $(OBJ_DIR) $(OBJ_LIST)
	@$(CC) $(OBJ_LIST) $(LIBS) -o $@ $(INCLUDE)
	@echo "$(NAME) created"

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(OBJ_DIR)$(SRC_DIR_FUNCTION)
	@mkdir -p $(OBJ_DIR)$(SRC_DIR_PARCER)
	@mkdir -p $(OBJ_DIR)$(SRC_DIR_UTILS)
	@echo "$(OBJ_DIR) created"

$(OBJ_DIR)%.o : $(SRC_DIR)%.c $(HDR) $(LIBFT)
	@$(CC) $(FLAGS) -c $< -o $@ $(INCLUDE)

$(LIBFT): $(LIBFT_OBJ)
	@$(MAKE) $(LIBFT_DIR)
	@echo "$(LIBFT) created"

#bonus: $(NAME)

clean:
	@$(MAKE) $(LIBFT_DIR) clean
	@echo "$(LIBFT_DIR)*.o deleted"
	@rm -rf $(OBJ_DIR)
	@echo "$(OBJ_DIR) deleted"

fclean: clean
	@$(MAKE) $(LIBFT_DIR) fclean
	@echo "$(LIBFT) deleted"
	@rm -rf $(NAME)
	@echo "$(NAME) deleted"

re: fclean all