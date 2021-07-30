/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olidon <olidon@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/02 14:04:45 by olidon            #+#    #+#             */
/*   Updated: 2021/01/19 14:35:21 by olidon           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_ONE_H
# define PHILO_ONE_H

# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <string.h>
# include <limits.h>

typedef struct		s_philo
{
	unsigned int	*args;
	int				argc;
	pthread_t		*philo_nbr;
	pthread_mutex_t	*forks_mutex;
	pthread_mutex_t	*write_mutex;
	pthread_mutex_t	*death_mutex;
	int				*ret;
	unsigned int	i;
	unsigned int	j;
	long int		time;
	unsigned int	nb_time_eating;
	long int		death_time;
	unsigned int	time_to_sleep;
	unsigned int	time_to_eat;
}					t_philo;

typedef struct		s_last_meal
{
	unsigned int	i;
	long int		init_time;
	long int		time;
	pthread_mutex_t	*death_mutex;
	pthread_mutex_t	*write_mutex;
	pthread_mutex_t	last_meal_mutex[1];
	int				*ret;
	long int		death_time;
	pthread_t		death_check;
	int				enough_eat;
	pthread_mutex_t	enough_eat_mutex[1];
}					t_last_meal;

int					main(int argc, char **argv);

void				*philo_routine(void *data);

void				*ft_check_death(void *data);

int					ft_init_struct(int argc, char **argv, t_philo *philo);
int					ft_mutexs_init(t_philo *philo);
t_last_meal			*ft_create_last_meal(t_philo *philo);

void				*ft_error_last_meal_free(int error,
							int tofree, t_last_meal *last_meal, t_philo *philo);
int					ft_error_free(int error, int tofree, t_philo *philo);
int					ft_destroy_mutexes(t_philo *philo, int error,
												int tofree, unsigned int size);
void				*ft_free_last_meal(t_last_meal *last_meal);

int					ft_is_last_fork(t_philo *philo);
int					ft_isnumber(char *str);
unsigned long long	ft_atoi(char *str);
void				ft_putstr(char *s);
void				ft_sleep_time(long int ref_time);

size_t				ft_strlen(const char *s);

int					ft_write_action(int phil_nbr, t_philo *philo, int action);
int					ft_write_death(int phil_nbr, t_last_meal *last_meal);

#endif
