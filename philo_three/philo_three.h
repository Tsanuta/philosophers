/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_three.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: olidon <olidon@student.42lyon.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/02 14:04:45 by olidon            #+#    #+#             */
/*   Updated: 2021/01/21 14:19:21 by olidon           ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_THREE_H
# define PHILO_THREE_H

# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <string.h>
# include <semaphore.h>
# include <signal.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <limits.h>

typedef struct		s_philo
{
	unsigned int	*args;
	int				argc;
	pid_t			*philo_nbr;
	sem_t			*forks_mutex;
	sem_t			*write_mutex;
	sem_t			*is_dead_sem;
	unsigned int	i;
	unsigned int	j;
	long int		time;
	unsigned int	nb_time_eating;
	long int		death_time;
	unsigned int	time_to_sleep;
	unsigned int	time_to_eat;
	sem_t			**last_meal_sem;
	char			**last_meal_name;
	sem_t			**enough_eat_sem;
	char			**enough_eat_name;
	sem_t			**ate_enough_sem;
	char			**ate_enough_name;
	int				enough_eat;
	pthread_t		death_check;
	long int		init_time;
}					t_philo;

typedef struct		s_phi
{
	int				argc;
	sem_t			*forks_mutex;
	sem_t			*write_mutex;
	sem_t			*is_dead_sem;
	unsigned int	i;
	unsigned int	j;
	long int		time;
	unsigned int	nb_time_eating;
	long int		death_time;
	unsigned int	time_to_sleep;
	unsigned int	time_to_eat;
	sem_t			*last_meal_sem;
	sem_t			*enough_eat_sem;
	sem_t			*ate_enough_sem;
	int				enough_eat;
	pthread_t		death_check;
	long int		init_time;
}					t_phi;

int					main(int argc, char **argv);

void				philo_routine(t_phi *philo);

void				*ft_check_death(void *data);

int					ft_init_struct(int argc, char **argv, t_philo *philo);
int					ft_mutexs_init(t_philo *philo);
int					ft_init_phi_sem(t_philo *phi);
int					ft_create_last_meal(t_phi *philo);

int					ft_fork_error(t_philo *philo, unsigned int index);

int					ft_error_free(int error, int tofree, t_philo *philo);
int					ft_destroy_sem(t_philo *philo, int error,
														int tofree, int index);
void				*ft_free_last_meal(t_phi *philo);

int					ft_isnumber(char *str);
unsigned long long	ft_atoi(char *str);
void				ft_putstr(char *s);
void				ft_sleep_time(long int ref_time);

char				*ft_strjoin(char *s1, char *s2);
char				*ft_itoa(int n);
size_t				ft_strlen(const char *s);

int					ft_write_action(int phil_nbr, t_phi *philo, int action);
int					ft_write_death(int phil_nbr, t_phi *philo);

int					ft_start_kill_threads(t_philo *philo);

#endif
