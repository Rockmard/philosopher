/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpipi <tpipi@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/14 13:51:34 by tpipi             #+#    #+#             */
/*   Updated: 2024/08/30 17:49:18 by tpipi            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./philo.h"

long	ft_atoi(const char *str)
{
	long	nbr;
	size_t	i;

	nbr = 0;
	i = 0;
	while (str[i] == ' ' || ('\t' <= str[i] && str[i] <= '\r'))
		i++;
	if (!('0' <= str[i] && str[i] <= '9'))
		return (-1);
	while ('0' <= str[i] && str[i] <= '9')
	{
		if (!('0' <= str[i] && str[i] <= '9'))
			return (-1);
		if (nbr > 2147483647)
			return (-1);
		nbr = nbr * 10 + str[i] - '0';
		i++;
	}
	if (str[i] && !('0' <= str[i] && str[i] <= '9'))
		return (-1);
	return (nbr);
}

static int	ft_parsing(char **av, int ac)
{
	int	i;

	i = 1;
	while (i < ac)
	{
		if (ft_atoi(av[i]) == 0 && i == 1)
		{
			ft_puterr("Can't run with no philosopher.\n");
			return (1);
		}
		if (ft_atoi(av[i]) == -1)
		{
			ft_puterr("Bad syntax at : ");
			ft_puterr(av[i]);
			ft_puterr("\n");
			return (1);
		}
		i++;
	}
	return (0);
}

static int	ft_arg_check(int ac, char **av)
{
	if (ac < 5)
	{
		ft_puterr(LESS_ARG_ERROR);
		return (1);
	}
	if (ac > 6)
	{
		ft_puterr(MORE_ARG_ERROR);
		return (1);
	}
	if (ft_parsing(av, ac))
		return (1);
	return (0);
}

int	main(int ac, char **av)
{
	t_data			*data;

	if (ft_arg_check(ac, av))
		return (1);
	data = create_data(av);
	if (!data)
		return (1);
	init_threads(data);
	thread(data);
	destroy_threads(data);
	free(data->list);
	free(data->fork);
	free(data->threads);
	free(data);
	return (0);
}
