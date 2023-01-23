#---------------------------------------------------#
CC 			= cc

CFLAGS 		= -Wall -Wextra -Werror 

NAME 		= minishell
#---------------------------------------------------#
OBJ_DIR 	= obj/

SRC_DIR		= src/

SRCS_FILES	= \


SRCS		= $(addprefix $(SRC_DIR), $(SRCS_FILES))

OBJS		= $(addprefix $(OBJ_DIR), ${SRCS_FILES:.c=.o})

INCLUDES 	= includes/minishell.h
#---------------------------------------------------#
LIBFT_DIR	= libft/

LIBFT_NAME	= libftprintf.a

LIBFT_EXEC	= $(addprefix $(LIBFT_DIR), $(LIBFT_NAME))
#---------------------------------------------------#
all: 
	@$(MAKE) -j $(NAME)

$(NAME): $(OBJ_DIR) $(LIBFT_EXEC) $(SRCS) $(OBJS) $(INCLUDES) 
	@$(CC) $(CFLAGS) $(LIBFT_EXEC) $(OBJS) -o $(NAME)

$(OBJ_DIR)%.o : $(SRC_DIR)$(notdir %.c) Makefile $(INCLUDES)
	$(CC) $(CFLAGS) -I $(INCLUDES) -c $< -o $@

$(OBJ_DIR):
	@mkdir $(OBJ_DIR)

$(LIBFT_EXEC):
	@$(MAKE) -C $(LIBFT_DIR) bonus 

clean:
	@$(MAKE) -C $(LIBFT_DIR) clean
	@rm -rf $(OBJ_DIR)

fclean: clean
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@rm -rf $(NAME)

re:	fclean
	@$(MAKE) -C $(LIBFT_DIR) re
	@$(MAKE) all

.PHONY: all clean fclean re
#---------------------------------------------------#
