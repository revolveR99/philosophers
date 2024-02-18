# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: zabdulza <zabdulza@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/01/20 09:37:16 by zabdulza          #+#    #+#              #
#    Updated: 2024/01/20 09:37:20 by zabdulza         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= philo
CC	= cc -g
CFLAGS	= -pthread -Wall -Werror -Wextra
SRC = $(wildcard *.c)
OBJS	= $(SRC:.c=.o)
.PHONY: all clean fclean re valgrind helgrind

.o: .c
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS) $(NAME_H) 
	$(CC) $(CFLAGS) $(OBJS) -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

valgrind: $(NAME)
	valgrind ./$(NAME) 5 800 200 200 7

helgrind: $(NAME)
	valgrind --tool=helgrind ./$(NAME) 5 800 200 200 7
