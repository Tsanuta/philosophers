# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: olidon <olidon@student.42lyon.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/10/02 13:56:34 by olidon            #+#    #+#              #
#    Updated: 2021/01/21 12:55:38 by olidon           ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

HEADER			=		philo_three.h

SRCS			=		philo_three.c			\
						philosophers.c			\
						write_actions.c			\
						init_struct.c			\
						init_sem.c				\
						check_death_thread.c	\
						free_error.c			\
						ft_fork_error.c			\
						utils.c					\
						utils2.c				\
						ft_kill_threads.c

OBJS			= 		${SRCS:.c=.o}

NAME			=		philo_three

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
