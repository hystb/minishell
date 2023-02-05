#---------------------------------------------------#
CC 			= cc

CFLAGS 		= 

NAME 		= minishell
#---------------------------------------------------#
OBJ_DIR 	= obj/

SRC_DIR		= pipex/

SRCS_FILES	= \
commands.c\
do_pipe.c\
exit_error.c\
get_path.c\
main.c\
redirections.c

SRCS		= $(addprefix $(SRC_DIR), $(SRCS_FILES))

OBJS		= $(addprefix $(OBJ_DIR), ${SRCS_FILES:.c=.o})

INCLUDES 	= ../includes/exec.h
#---------------------------------------------------#
LIBFT_DIR	= ../libft/

LIBFT_NAME	= libftprintf.a

LIBFT_EXEC	= $(addprefix $(LIBFT_DIR), $(LIBFT_NAME))
#---------------------------------------------------#
all: lib
	$(MAKE) -j $(NAME)

$(NAME): $(OBJ_DIR) $(SRCS) $(OBJS) $(INCLUDES)
	$(CC) -lreadline $(CFLAGS) $(OBJS) -o $(NAME) $(LIBFT_EXEC)

$(OBJ_DIR)%.o : $(SRC_DIR)$(notdir %.c) Makefile $(INCLUDES)
	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir $(OBJ_DIR)

lib:
	$(MAKE) -C $(LIBFT_DIR)

clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	rm -rf $(OBJ_DIR)

fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	rm -rf $(NAME)

re:	fclean
	$(MAKE) -C $(LIBFT_DIR) re
	$(MAKE) all

.PHONY: all clean fclean re
#---------------------------------------------------#