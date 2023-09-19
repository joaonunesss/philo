# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jmarinho <jmarinho@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/19 15:16:10 by jmarinho          #+#    #+#              #
#    Updated: 2023/09/19 15:40:07 by jmarinho         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo
CFLAGS = -pthread -Wall -Wextra -Werror -g
RM = rm -f
SRCS = src/1_philo.c src/2_initializations.c src/3_surveillance.c \
		src/4_simulation_utils.c src/5_utils.c

S_OBJS = $(SRCS:.c=.o)

all: $(S_OBJS)
	@cc $(CFLAGS) $(S_OBJS) -o $(NAME) -I.
	printf "Executable ./$(NAME) was created.\n"

clean:
	@$(RM) $(S_OBJS)
	printf "Object files were removed.\n"

fclean: clean
	@$(RM) $(NAME)
	printf "Executable ./$(NAME) was removed.\n"

re: fclean all

.PHONY: all clean fclean re
.SILENT:
