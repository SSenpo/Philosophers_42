/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmago <mmago@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 16:47:23 by mmago             #+#    #+#             */
/*   Updated: 2022/06/12 22:39:07 by mmago            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	ft_check_arg(char **av)
{
	int	i;
	int	check;

	i = 1;
	while (av[i])
	{
		check = ft_atoi(av[i]);
		if (check == ERROR)
			return (check);
		i++;
	}
	return (SUCCESS);
}

int	ft_parse_arg(int ac, char **av)
{
	t_all	all;

	all.args = malloc(sizeof(t_args));
	if (ft_check_arg(av) == ERROR)
	{
		free(all.args);
		return (FAIL);
	}
	// all.args->flag = 0;
	all.args->num_ph = ft_atoi(av[1]);
	all.args->time_die = ft_atoi(av[2]);
	all.args->time_eat = ft_atoi(av[3]);
	all.args->time_sleep = ft_atoi(av[4]);
	all.args->must_eat = 0;
	if (ac == 6)
		all.args->must_eat = ft_atoi(av[5]);
	if (ft_init_philos(&all) == FAIL)
	{
		ft_free(&all);
		return (FAIL);
	}
	return (SUCCESS);
}

int	main(int ac, char **av)
{
	if (ac == 5 || ac == 6)
	{
		if (ft_parse_arg(ac, av) == FAIL)
			return (FAIL);
	}
	else
		ft_error(2);
	return (SUCCESS);
}
