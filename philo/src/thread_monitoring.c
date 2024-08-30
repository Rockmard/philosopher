/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_monitoring.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpipi <tpipi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 00:57:52 by tpipi             #+#    #+#             */
/*   Updated: 2024/08/27 01:11:37 by tpipi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

static void	ft_massacre(t_philo *philo, int nb_kill)
{
	int	i;

	i = 0;
	while (i < nb_kill)
	{
		pthread_mutex_lock(&philo->data->mutex_tab[1]);
		philo[i].status = DEAD;
		pthread_mutex_unlock(&philo->data->mutex_tab[1]);
		i++;
	}
}

static void	threads_state_process(t_data *data, int i)
{
	int				diff;
	int				nb_success;
	int				time;

	pthread_mutex_lock(&data->mutex_tab[3]);
	nb_success = data->nb_success;
	pthread_mutex_unlock(&data->mutex_tab[3]);
	if (nb_success == data->nb_philo)
	{
		pthread_mutex_lock(&data->mutex_tab[2]);
		data->thread_run = 0;
		pthread_mutex_unlock(&data->mutex_tab[2]);
	}
	time = get_time();
	pthread_mutex_lock(&data->mutex_tab[4]);
	diff = time - data->list[i].last_time_ate;
	pthread_mutex_unlock(&data->mutex_tab[4]);
	if (diff > data->list[i].time_to_die && nb_success < data->nb_philo)
	{
		threadsafe_print(&data->list[i], DEATH_MSG);
		ft_massacre(data->list, data->nb_philo);
		pthread_mutex_lock(&data->mutex_tab[2]);
		data->thread_run = 0;
		pthread_mutex_unlock(&data->mutex_tab[2]);
	}
}

void	*thread_monitoring(void *var)
{
	int				i;
	int				thread_run;
	t_data			*data;

	data = (t_data *)var;
	while (1)
	{
		i = 0;
		pthread_mutex_lock(&data->mutex_tab[2]);
		thread_run = data->thread_run;
		pthread_mutex_unlock(&data->mutex_tab[2]);
		while (i < data->nb_philo)
		{
			threads_state_process(data, i);
			i++;
		}
		if (!thread_run)
			break ;
	}
	return (NULL);
}
