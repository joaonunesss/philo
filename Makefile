# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jmarinho <jmarinho@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/04 12:44:40 by jmarinho          #+#    #+#              #
#    Updated: 2023/09/06 17:23:37 by jmarinho         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

SRC = src/philo.c src/philo_monitoring.c src/philo_utils.c src/start_philosophers.c \

OBJS = ${SRC:.c=.o}

RM = rm -f

FLAGS = -Wall -Wextra -Werror -g

all: ${OBJS}
	cc ${FLAGS} ${OBJS} -pthread -o ${NAME}

clean:
	${RM} ${OBJS}

fclean: clean
	${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re

.SILENT: