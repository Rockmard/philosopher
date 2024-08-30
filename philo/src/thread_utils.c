/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpipi <tpipi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 06:18:42 by tpipi             #+#    #+#             */
/*   Updated: 2024/08/27 02:19:17 by tpipi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

int	get_time(void)
{
	struct timeval	current_time;
	int				realtime;

	if (gettimeofday(&current_time, NULL) == -1)
	{
		ft_puterr("Couldn't get the time.");
		return (0);
	}
	realtime = ((current_time.tv_sec) * 1000) + ((current_time.tv_usec) / 1000);
	return (realtime);
}

int	ft_usleep(t_philo *philo, int sleeping_time)
{
	int	status;
	int	init_time;

	init_time = get_time();
	while (get_time() < init_time + sleeping_time)
	{
		pthread_mutex_lock(&philo->data->mutex_tab[1]);
		status = philo->status;
		pthread_mutex_unlock(&philo->data->mutex_tab[1]);
		if (status != ALIVE)
			break ;
		usleep(50);
	}
	return (0);
}

void	init_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		pthread_mutex_init(&data->fork[i], NULL);
		i++;
	}
	i = 0;
	while (i < 5)
	{
		pthread_mutex_init(&data->mutex_tab[i], NULL);
		i++;
	}
}

void	destroy_threads(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		pthread_mutex_destroy(&data->fork[i]);
		i++;
	}
	i = 0;
	while (i < 5)
	{
		pthread_mutex_destroy(&data->mutex_tab[i]);
		i++;
	}
}
