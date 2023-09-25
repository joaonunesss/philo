# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jmarinho <jmarinho@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/19 15:16:10 by jmarinho          #+#    #+#              #
#    Updated: 2023/09/25 12:51:28 by jmarinho         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

RED := \033[0;31m
GREEN := \033[0;32m
YELLOW := \033[0;33m
RESET := \033[0m

NAME = philo
FLAGS = -Wall -Wextra -Werror -g -pthread -fsanitize=thread
RM = rm -f
SRCS = src/1_philo.c src/2_initializations.c src/3_surveillance.c \
		src/4_simulation_utils.c src/5_utils.c

OBJS = $(SRCS:.c=.o)

all: $(OBJS)
	@cc $(FLAGS) $(OBJS) -o $(NAME)
	printf "$(GREEN)Executable ./$(NAME) was created.\n$(RESET)"

clean:
	@$(RM) $(OBJS)
	printf "$(YELLOW)Object files were removed.\n$(RESET)"

fclean: clean
	@$(RM) $(NAME)
	printf "$(RED)Executable ./$(NAME) was removed.\n$(RESET)"

re: fclean all

.PHONY: all clean fclean re

.SILENT:
