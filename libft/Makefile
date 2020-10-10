NAME = libft.a
NAME_SO = libft.so

HDRS = ./

SRCS = ft_memset.c ft_bzero.c ft_memcpy.c ft_memccpy.c ft_memmove.c \
ft_memchr.c ft_memcmp.c ft_strlen.c ft_strlcpy.c ft_strlcat.c ft_strchr.c \
ft_strrchr.c ft_strnstr.c ft_strncmp.c ft_atoi.c ft_isalpha.c ft_isdigit.c \
ft_isalnum.c ft_isascii.c ft_isprint.c ft_toupper.c ft_tolower.c \
ft_calloc.c ft_strdup.c ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c \
ft_itoa.c ft_strmapi.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c \
ft_putnbr_fd.c ft_strcmp.c ft_strpass.c

OBJS = $(SRCS:.c=.o)

CC = @gcc -Wall -Wextra -Werror
AR = @ar -rcs
RM = @rm -f

.PHONY: all so clean fclean re

%.o: %.c $(HRDS)libft.h
	$(CC) -c $< -o ${<:.c=.o} -I $(HDRS)

all: $(NAME)

$(NAME): $(OBJS)
	$(AR) $(NAME) $(OBJS)

so:
	${CC} -shared -o $(NAME_SO) -fPIC $(SRCS)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME) $(NAME_SO)

re: fclean all
