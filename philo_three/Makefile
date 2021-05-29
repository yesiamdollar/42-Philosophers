# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aboutahr <aboutahr@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/05/26 20:15:42 by aboutahr          #+#    #+#              #
#    Updated: 2021/05/28 18:12:37 by aboutahr         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME=philo_three

SRCS=exit.c life.c main.c semaphore.c threads.c utils.c

FLAGS=-Wall -Wextra -Werror -lpthread

ALL: $(NAME)
 
$(NAME):
	gcc ${FLAGS} ${SRCS} -o ${NAME}

clean:
	rm -f ${NAME}

fclean: clean

re: fclean ALL