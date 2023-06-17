# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ocastell <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/08 11:29:44 by ocastell          #+#    #+#              #
#    Updated: 2022/10/08 11:39:02 by ocastell         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc
CFLAGS = -Wall -Wextra -Werror
INC = -I.
AR = ar
ARF = -rcs
NAME = libft.a

MAN = isalpha isdigit isalnum isascii isprint strlen memset bzero memcpy\
		memmove strlcpy strlcat toupper tolower strchr strrchr strncmp memchr\
		memcmp strnstr atoi calloc strdup substr strjoin strtrim split itoa\
		strmapi striteri putchar_fd putstr_fd putendl_fd putnbr_fd\
		printf print_p print_s putchars_fd putnbrs_fd putnbru_fd\
		putnbr_X putstrs_fd putnbr_base_fd get_next_line\
		lstnew lstadd_front lstsize lstlast lstadd_back lstdelone lstclear\
		lstiter lstmap
MANFC = $(addprefix ft_,$(addsuffix .c, $(MAN)))
MANO = $(MANFC:.c=.o)

BON = lstnew lstadd_front lstsize lstlast lstadd_back lstdelone lstclear\
		lstiter lstmap
BONFC = $(addprefix ft_,$(addsuffix .c, $(BON)))
BONO = $(BONFC:.c=.o)

all: $(NAME)

$(NAME): $(MANO)
	$(AR) $(ARF) $@ $^

%.o: %.c
	@$(CC) -c $(CFLAGS) $(INC) $< -o $@

clean:
	@rm -f $(MANO) $(BONO)

fclean: clean
	@rm -f $(NAME)

re: fclean all

bonus:	$(BONO)
	$(AR) $(ARF) $(NAME) $^

.PHONY: bonus all clean fclean re