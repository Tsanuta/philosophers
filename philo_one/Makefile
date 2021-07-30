# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: olidon <olidon@student.42lyon.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/10/02 13:56:34 by olidon            #+#    #+#              #
#    Updated: 2021/01/20 15:24:21 by olidon           ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

HEADER			=		philo_one.h

SRCS			=		philo_one.c				\
						philosophers.c			\
						write_actions.c			\
						init_struct.c			\
						check_death_thread.c	\
						free_error.c			\
						utils.c					\
						utils2.c

OBJS			= 		${SRCS:.c=.o}

NAME			=		philo_one

# FLAGS			+=		-g3 -Wall -Wextra -Werror -fsanitize=address
FLAGS			+=		-g3 -Wall -Wextra -Werror -pthread

all				:		$(NAME)

%.o				:		%.c $(HEADER)
						gcc $(FLAGS) -c $< -o $(<:.c=.o)

$(NAME)			:		$(OBJS)
						gcc $(FLAGS) -o $(NAME) $(OBJS)

clean			:
						rm -f $(OBJS)

fclean			:		clean
						rm -f $(NAME)

re				:      	fclean all

.PHONY			:		all lib clean fclean re
