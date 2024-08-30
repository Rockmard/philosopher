/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpipi <tpipi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 02:00:25 by tpipi             #+#    #+#             */
/*   Updated: 2024/08/27 03:47:43 by tpipi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

static int	eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->fork[philo->id - 1]);
	threadsafe_print(philo, FORK_MSG);
	if (philo->data->nb_philo == 1)
	{
		pthread_mutex_unlock(&philo->data->fork[philo->id - 1]);
		return (1);
	}
	if (philo->id == 1)
		pthread_mutex_lock(&philo->data->fork[philo->data->nb_philo - 1]);
	else
		pthread_mutex_lock(&philo->data->fork[philo->id - 2]);
	threadsafe_print(philo, FORK_MSG);
	threadsafe_print(philo, EAT_MSG);
	philo->nb_time_ate++;
	return (0);
}

static void	pre_sleep(t_philo *philo)
{
	int	time;

	if (philo->nb_time_ate == philo->nb_need_eat)
	{
		pthread_mutex_lock(&philo->data->mutex_tab[3]);
		philo->data->nb_success++;
		pthread_mutex_unlock(&philo->data->mutex_tab[3]);
		pthread_mutex_lock(&philo->data->mutex_tab[1]);
		philo->status = FULL;
		pthread_mutex_unlock(&philo->data->mutex_tab[1]);
	}
	ft_usleep(philo, philo->time_to_eat);
	time = get_time();
	pthread_mutex_lock(&philo->data->mutex_tab[4]);
	philo->last_time_ate = time;
	pthread_mutex_unlock(&philo->data->mutex_tab[4]);
	pthread_mutex_unlock(&philo->data->fork[philo->id - 1]);
	if (philo->id == 1)
		pthread_mutex_unlock(&philo->data->fork[philo->data->nb_philo - 1]);
	else
		pthread_mutex_unlock(&philo->data->fork[philo->id - 2]);
}

static void	*thread_dinner(void *var)
{
	t_philo			*philo;
	int				end;

	philo = (t_philo *)var;
	if (philo->id % 2 == 0)
		ft_usleep(philo, philo->time_to_eat);
	while (philo->nb_need_eat != 0)
	{
		if (eat(philo))
			break ;
		pre_sleep(philo);
		threadsafe_print(philo, SLEEP_MSG);
		ft_usleep(philo, philo->time_to_sleep);
		threadsafe_print(philo, THINK_MSG);
		usleep(350);
		pthread_mutex_lock(&philo->data->mutex_tab[2]);
		end = philo->data->thread_run;
		pthread_mutex_unlock(&philo->data->mutex_tab[2]);
		if (end == 0)
			break ;
	}
	return (NULL);
}

void	thread(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nb_philo)
	{
		data->list[i].last_time_ate = get_time();
		if (pthread_create(&data->threads[i], NULL, &thread_dinner, \
			(void *)&data->list[i]) != 0)
			return ;
		i++;
	}
	if (pthread_create(&data->death_thread, NULL, \
		&thread_monitoring, (void *)data) != 0)
		return ;
	i = 0;
	while (i < data->nb_philo)
	{
		if (pthread_join(data->threads[i], NULL) != 0)
			return ;
		i++;
	}
	if (pthread_join(data->death_thread, NULL) != 0)
		return ;
}
