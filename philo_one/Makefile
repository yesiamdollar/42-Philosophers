# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aboutahr <aboutahr@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/05/26 20:15:42 by aboutahr          #+#    #+#              #
#    Updated: 2021/05/26 20:41:36 by aboutahr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=philo_one

SRCS=exit.c life.c main.c mutex.c threads.c utils.c

OBJS= $(SRCS:.c=.o)

FLAG=-g -fsanitize=address

FLAGS=-Wall -Wextra -Werror -I. -lpthread

ALL: $(NAME)
 
$(NAME): $(OBJS)
	gcc ${FLAGS} ${OBJS} -o ${NAME} 

clean:
	rm -f ${OBJS}

fclean: clean
	rm -f philo_one

re: fclean ALL