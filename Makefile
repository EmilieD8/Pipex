# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: edrouot <edrouot@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/12/11 13:11:53 by edrouot           #+#    #+#              #
#    Updated: 2023/04/10 15:47:08 by edrouot          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= pipex

LIBFT = Libft/libft.a

SRCS	= pipex.c

OBJS	= $(SRCS:.c=.o)

CC 	= cc

CFLAGS = -Wall -Wextra -Werror

all:	$(NAME)

${NAME}: $(OBJS)
	@make -C ./Libft
	$(CC) $(SRCS) $(LIBFT) $(CFLAGS) -o $(NAME)

clean: 
	@rm -f $(OBJS)
	@make clean -C Libft

fclean: clean
	@rm -f $(NAME)
	@rm -f $(LIBFT)

re:	fclean all

.PHONY:	all clean fclean re
