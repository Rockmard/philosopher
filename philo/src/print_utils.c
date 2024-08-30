/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpipi <tpipi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/02 14:29:54 by tpipi             #+#    #+#             */
/*   Updated: 2024/08/27 01:11:43 by tpipi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

static unsigned long long	ft_strlen(const char *str)
{
	unsigned long long	i;

	i = 0;
	while (str && str[i])
		i++;
	return (i);
}

unsigned long long	ft_puterr(const char *s)
{
	if (s)
		return (write(2, s, ft_strlen(s)));
	return (0);
}

int	threadsafe_print(t_philo *philo, char *str)
{
	int				res;
	int				philo_status;
	int				time;

	res = 0;
	time = get_time();
	pthread_mutex_lock(&philo->data->mutex_tab[0]);
	pthread_mutex_lock(&philo->data->mutex_tab[1]);
	philo_status = philo->status;
	pthread_mutex_unlock(&philo->data->mutex_tab[1]);
	if (philo_status == ALIVE)
	{
		res = printf("%ld %d %s\n", time - \
		philo->data->base_ms, philo->id, str);
	}
	pthread_mutex_unlock(&philo->data->mutex_tab[0]);
	return (res);
}
