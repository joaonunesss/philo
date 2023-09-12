# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ride-sou <ride-sou@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/04/02 20:09:19 by ccosta-c          #+#    #+#              #
#    Updated: 2023/07/03 12:14:55 by ride-sou         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#_/=\_/=\_/=\_/=\_/=\_/=\_/=\_/=\_/=\_/=\_ COLORS _/=\_/=\_/=\_/=\_/=\_/=\_/=\_/=\_/=\_/=\_
RESET	= \033[0m
BLACK 	= \033[1;30m
RED 	= \033[1;31m
GREEN 	= \033[1;32m
YELLOW 	= \033[1;33m
BLUE	= \033[1;34m
PURPLE 	= \033[1;35m
CYAN 	= \033[1;36m
WHITE 	= \033[1;37m

#_/=\_/=\_/=\_/=\_/=\_/=\_/=\_/=\_/=\_/=\_ COMMANDS _/=\_/=\_/=\_/=\_/=\_/=\_/=\_/=\_/=\_/=\_
CC = cc
RM = rm -f
AR = ar -rcs

#_/=\_/=\_/=\_/=\_/=\_/=\_/=\_/=\_/=\_/=\_ FLAGS _/=\_/=\_/=\_/=\_/=\_/=\_/=\_/=\_/=\_/=\_-fsanitize=thread
CFLAGS		= -Wall -Wextra -Werror -g -pthread -fsanitize=thread
MKFLAGS		= --no-print-directory

#_/=\_/=\_/=\_/=\_/=\_/=\_/=\_/=\_/=\_/=\_ FOLDERS _/=\_/=\_/=\_/=\_/=\_/=\_/=\_/=\_/=\_/=\_
DEPS		= includes
SRCS		= .
SRCS_BONUS	= bonus

#_/=\_/=\_/=\_/=\_/=\_/=\_/=\_/=\_/=\_/=\_ FILES _/=\_/=\_/=\_/=\_/=\_/=\_/=\_/=\_/=\_/=\_
SRC				= utils.c initialize.c actions.c overseer.c utils_2.c
OBJS 			:= $(SRC:.c=.o)
BONUS			=
OBJS_BONUS		:= $(BONUS:.c=.o)
NAME			= philo
NAME_BONUS		= philo
TARGET			= $(addprefix $(SRCS)/, $(OBJS))
TARGET_BONUS	= $(addprefix $(SRCS_BONUS)/, $(OBJS_BONUS))


#_/=\_/=\_/=\_/=\_/=\_/=\_/=\_/=\_/=\_/=\_ RULES _/=\_/=\_/=\_/=\_/=\_/=\_/=\_/=\_/=\_/=\_
all: $(NAME)

$(NAME): $(TARGET)
	$(CC) $(CFLAGS) main.c $(TARGET) $(LIBFTFLAGS) -o $(NAME)

	echo "$(GREEN)Done.$(RESET)"

%.o : %.c
	echo "[$(CYAN)Compiling$(RESET)] $(CFLAGS) $(GREEN)$<$(RESET)"
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	echo "[$(RED) Deleted $(RESET)] $(GREEN)*/*.o$(RESET)"
	$(RM) $(TARGET) $(TARGET_BONUS)

fclean: clean
	echo "[$(RED) Deleted $(RESET)] $(GREEN)$(NAME)$(RESET)"
	$(RM) $(NAME)
	$(RM) $(NAME_BONUS)

bonus: $(TARGET_BONUS)
	$(CC) $(CFLAGS) bonus/main.c $(TARGET_BONUS) $(LIBFTFLAGS) -o $(NAME_BONUS) -I $(DEPS)
	echo "$(GREEN)Done.$(RESET)"

re: fclean all

.SILENT:
