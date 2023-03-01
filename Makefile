#---------------------------------------------------#
CC 			= cc

CFLAGS 		= -fsanitize=address -g3 

NAME 		= minishell
#---------------------------------------------------#
OBJ_DIR 	= obj/

EXIT_DIR	= exit/

EXIT_FILES	= \
exit_error.c\
exit_lst.c

EXEC_DIR	= exec/

EXEC_FILES	= \
utils.c\
do_exec.c\
do_pipe.c\
get_path.c\
redirections_cases.c\
redirections.c

PARS_DIR	= pars/

PARS_FILES	= input.c\
make_map.c\
pipe_sign.c\
put_lst.c\
space_pipe.c\
utils_pars.c\
replace_env.c\
env_lst.c

SRCS		= $(addprefix $(PARS_DIR), $(PARS_FILES)) $(addprefix $(EXIT_DIR), $(EXIT_FILES)) $(addprefix $(EXEC_DIR), $(EXEC_FILES)) main.c builtins/export.c builtins/echo.c

OBJS		= $(SRCS:%.c=%.o)

INCLUDES 	= includes/exec.h includes/minishell.h
#---------------------------------------------------#
LIBFT_DIR	= libft/

LIBFT_NAME	= libftprintf.a

LIBFT_EXEC	= $(addprefix $(LIBFT_DIR), $(LIBFT_NAME))
#---------------------------------------------------#
all: lib
	$(MAKE) -j $(NAME)

$(NAME): $(OBJ_DIR) $(OBJS) $(INCLUDES)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -I includes/ -lreadline -ltinfo $(LIBFT_EXEC)

$(OBJ_DIR)%.o : $(EXEC_DIR)%.c $(EXIT_DIR)%.c $(PARS_DIR)%.c Makefile $(INCLUDES)
	$(CC) $(CFLAGS) -c $< -o $@

# $(OBJ_DIR)%.o : $(SRC_DIR)$(notdir %.c) Makefile $(INCLUDES)
# 	$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	mkdir $(OBJ_DIR)

lib:
	$(MAKE) -C $(LIBFT_DIR)

clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	rm -rf $(OBJ_DIR)
	rm -rf $(OBJS)

fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	rm -rf $(NAME)

re:	fclean
	$(MAKE) -C $(LIBFT_DIR) re
	$(MAKE) all

.PHONY: all clean fclean re
#---------------------------------------------------#
