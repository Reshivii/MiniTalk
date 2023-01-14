# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aburnott <aburnott@student.s19.be>         +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/01/14 18:15:32 by aburnott          #+#    #+#              #
#    Updated: 2023/01/14 19:18:37 by aburnott         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = client
S_NAME = server
SRCS = SRCS/client.c SRCS/utils.c ft_printf/ft_printf.c ft_printf/ft_utils.c
S_SRCS = SRCS/server.c SRCS/utils.c ft_printf/ft_printf.c ft_printf/ft_utils.c
OBJS = $(SRCS:.c=.o)
S_OBJS = $(S_SRCS:.c=.o)
CC = gcc
CFLAGS = -Wall -Wextra

all: $(NAME) $(S_NAME)

$(S_NAME): $(S_OBJS)
	$(CC) $(CFLAGS) $(S_OBJS) -o $(S_NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)
clean:
	rm -f $(OBJS)
	rm -f $(S_OBJS)
fclean: clean
	rm -f $(NAME)
	rm -f $(S_NAME)
re: fclean all
.PHONY: all clean fclean re