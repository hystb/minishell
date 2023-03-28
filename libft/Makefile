#---------------------------------------------------#
CC 			= cc

CFLAGS 		= -Wall -Wextra -Werror

NAME 		= libftprintf.a
#---------------------------------------------------#
OBJ_DIR 	= obj/

SRCS		= ft_isalpha.c\
ft_isdigit.c\
ft_isalnum.c\
ft_isascii.c\
ft_isprint.c\
ft_strlen.c\
ft_memset.c\
ft_bzero.c\
ft_memcpy.c\
ft_memmove.c\
ft_strlcpy.c\
ft_strlcat.c\
ft_toupper.c\
ft_tolower.c\
ft_strchr.c\
ft_strrchr.c\
ft_strncmp.c\
ft_memchr.c\
ft_memcmp.c\
ft_strnstr.c\
ft_atoi.c\
ft_calloc.c\
ft_strdup.c\
ft_substr.c\
ft_strjoin.c\
ft_strtrim.c\
ft_split.c\
ft_itoa.c\
ft_strmapi.c\
ft_striteri.c\
ft_putchar_fd.c\
ft_putstr_fd.c\
ft_putendl_fd.c\
ft_putnbr_fd.c\
ft_printf.c\
put_hutils.c\
put_utils.c\
ft_lstnew.c\
ft_lstadd_front.c\
ft_lstsize.c\
ft_lstlast.c\
ft_lstadd_back.c\
ft_lstdelone.c\
ft_lstclear.c\
ft_lstiter.c\
ft_lstmap.c

OBJS		= $(addprefix $(OBJ_DIR), ${SRCS:.c=.o})

INCLUDES 	= libft.h
#---------------------------------------------------#

all: 
	$(MAKE) $(NAME)

$(NAME): $(OBJ_DIR) $(SRCS) $(OBJS) $(INCLUDES) 
	ar rc $(NAME) $(OBJS) 

$(OBJ_DIR)%.o : %.c Makefile $(INCLUDES)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir $(OBJ_DIR)

clean:
	rm -rf $(OBJS)
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -rf $(NAME)

re:	fclean all


.PHONY: all clean fclean re
#---------------------------------------------------#
