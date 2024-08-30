/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpipi <tpipi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/19 04:08:41 by tpipi             #+#    #+#             */
/*   Updated: 2024/08/30 17:18:29 by tpipi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

t_philo	init_philo(int id, char **av, t_data *data)
{
	t_philo	philo;

	philo.id = id;
	philo.status = ALIVE;
	philo.nb_time_ate = 0;
	philo.time_to_die = ft_atoi(av[2]);
	philo.time_to_eat = ft_atoi(av[3]);
	philo.time_to_sleep = ft_atoi(av[4]);
	philo.last_time_ate = 0;
	if (av[5])
		philo.nb_need_eat = ft_atoi(av[5]);
	else
		philo.nb_need_eat = -1;
	philo.data = data;
	return (philo);
}

t_philo	*create_list(char **av, int nb_philo, t_data *data)
{
	int		i;
	t_philo	*list;

	i = 1;
	list = malloc(sizeof(t_philo) * nb_philo);
	if (!list)
		return (NULL);
	while (i <= nb_philo)
	{
		list[i - 1] = init_philo(i, av, data);
		i++;
	}
	return (list);
}

t_data	*create_data(char **av)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (NULL);
	data->base_ms = get_time();
	data->thread_run = 1;
	data->nb_philo = ft_atoi(av[1]);
	data->nb_success = 0;
	data->list = create_list(av, data->nb_philo, data);
	data->fork = malloc(sizeof(pthread_mutex_t) * data->nb_philo);
	data->threads = malloc(sizeof(pthread_t) * data->nb_philo);
	if (!data->list || !data->fork || !data->threads)
	{
		ft_puterr(MEMORY_ERROR);
		free(data->list);
		free(data->fork);
		free(data->threads);
		free(data);
		return (NULL);
	}
	return (data);
}
