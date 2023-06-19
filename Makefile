BLU			= \033[0;34m
GRN			= \033[0;32m
RED			= \033[0;31m
RST			= \033[0m
END			= \e[0m

SRCS 		=	src/main.c src/utils.c src/command.c src/lexer.c src/node.c src/errors.c \
				src/exec.c src/parser.c src/ft_cd.c src/ft_export.c src/space_killer.c	\
				src/slashyer.c src/sep_pipe.c src/tokenization.c src/dollaroni.c \
				src/heredoc.c src/lexer_utils.c src/command_utils.c src/exec_utils.c \
				src/ft_export_if.c src/ft_export_realloc.c src/ft_export_utils.c \
				src/cd_utils.c src/cd_more_utils.c src/parser2.c src/parser3.c \
				src/parser4.c src/parserpipe.c src/parsereadir.c src/heredoc_utils.c \
				src/mainazzo.c src/releasalo.c src/puliscimelo.c
NAME		= minishell
OBJS_DIR	= objs/
OBJS		= $(SRCS:.c=.o)
OBJECTS_PREFIXED = $(addprefix $(OBJS_DIR), $(OBJS))
CC			= gcc -g
CC_FLAGS	= -Wall -Werror -Wextra
LIB_FLAG	= -L/usr/include -lreadline libft/libft.a
# added -lreadline to LIB_FLAG
$(OBJS_DIR)%.o : %.c includes/minishell.h
	@mkdir -p $(OBJS_DIR)
	@mkdir -p $(OBJS_DIR)src
	@$(CC) $(CC_FLAGS) -c $< -o $@
	@printf	"\033[2K\r${BLU}[BUILD - $(NAME)]${RST} '$<' $(END)"

$(NAME): $(OBJECTS_PREFIXED) maker
	@$(CC) -o $(NAME) $(OBJECTS_PREFIXED) $(CC_FLAGS) $(LIB_FLAG)
	@printf "\033[2K\r\033[0;32m[END]\033[0m $(NAME)$(END)\n"

all: $(NAME)

maker:
	@make -C libft

clean:
	@rm -rf $(OBJS_DIR)
	@make clean -C libft
	@echo "${GRN}[CLEAN]${RST} done"

fclean: clean
	@make fclean -C libft
	@rm -f $(NAME)
	@echo "${GRN}[FCLEAN]${RST} done"

re: fclean all

.PHONY:		all clean fclean re
