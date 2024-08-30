/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpipi <tpipi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 13:58:03 by tpipi             #+#    #+#             */
/*   Updated: 2024/08/30 17:25:55 by tpipi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <unistd.h>
# include <stdio.h>
# include <sys/time.h>
# include <stdlib.h>

# define MEMORY_ERROR "A memory error has occured\n"
# define MORE_ARG_ERROR "There's too many arguments\n"
# define LESS_ARG_ERROR "There isn't enough argument(s)\n"
# define FORK_MSG "has taken a fork"
# define EAT_MSG "is eating"
# define DEATH_MSG "died"
# define THINK_MSG "is thinking"
# define SLEEP_MSG "is sleeping"

# define ALIVE 0
# define DEAD 1
# define FULL 2

typedef struct s_philo
{
	int				id;
	int				nb_time_ate;
	int				nb_need_eat;
	int				time_to_eat;
	int				time_to_sleep;
	int				time_to_die;
	int				last_time_ate;
	int				status;
	struct s_data	*data;
}	t_philo;

/* mutex_tab
0 : print
1 : status
2 : thread_run
3 : nb_success
4 : last_time_ate
*/

typedef struct s_data
{
	int				thread_run;
	int				nb_philo;
	int				nb_success;
	long int		base_ms;
	struct s_philo	*list;
	pthread_t		death_thread;
	pthread_t		*threads;
	pthread_mutex_t	*fork;
	pthread_mutex_t	mutex_tab[5];
}	t_data;

t_philo				*create_list(char **av, int nb_philo, t_data *data);
t_data				*create_data(char **av);
void				init_threads(t_data *data);
void				destroy_threads(t_data *data);
void				thread(t_data *data);
void				*thread_monitoring(void *var);
int					threadsafe_print(t_philo *philo, char *str);
int					get_time(void);
int					ft_usleep(t_philo *philo, int sleeping_time);
long				ft_atoi(const char *str);
unsigned long long	ft_puterr(const char *s);

#endif