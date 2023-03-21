#---------------------------------------------------#
CC 			= cc

CFLAGS 		= -Wall -Wextra -Werror

OFLAGS		= -lreadline -ltinfo

NAME 		= minishell
#---------------------------------------------------#
OBJ_DIR 	= obj/

SRCS		= \
main.c\
builtins/echo.c\
builtins/export.c\
builtins/export_nargs.c\
builtins/pwd.c\
builtins/cd.c\
builtins/unset.c\
builtins/env.c\
builtins/exit.c\
builtins/builtins.c\
exec/do_exec.c\
exec/do_pipe.c\
exec/do_heredoc.c\
exec/get_path.c\
exec/gnl_main.c\
exec/gnl_utils.c\
exec/redirections_cases.c\
exec/redirections.c\
exec/env_utils.c\
exec/env_utils_aux.c\
exec/utils.c\
exit/exit_error.c\
exit/exit_lst.c\
pars/env_lst.c\
pars/error_pars.c\
pars/error_pipe.c\
pars/input.c\
pars/make_map.c\
pars/put_lst.c\
pars/replace_env.c\
pars/replace_quote.c\
pars/space_pipe.c\
pars/utils_pars.c

OBJ_DIR 	= .obj

OBJS		= $(SRCS:%.c=$(OBJ_DIR)/%.o)

INCLUDES 	= includes/

HEADERS		= includes/gnl.h includes/minishell.h
#---------------------------------------------------#
LIBFT_DIR	= libft/

LIBFT_NAME	= libftprintf.a

LIBFT_EXEC	= $(addprefix $(LIBFT_DIR), $(LIBFT_NAME))
#---------------------------------------------------#
all: lib
	$(MAKE) -j $(NAME)

$(NAME): $(OBJS) $(INCLUDES)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -I $(INCLUDES) $(OFLAGS) $(LIBFT_EXEC)

$(OBJ_DIR)/%.o : %.c Makefile $(HEADERS)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

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

.PHONY: all lib fclean fclean re
#---------------------------------------------------#
