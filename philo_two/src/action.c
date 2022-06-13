/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmago <mmago@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 16:39:51 by mmago             #+#    #+#             */
/*   Updated: 2022/06/13 18:18:51 by mmago            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	get_last_meal(t_philo *philo)
{
	philo->last_eat_time = ft_get_cur_time();
}

void	print_message(char *str, t_philo *philo)
{
	if (philo->dead_flag == 0)
	{
		sem_wait(philo->all->sems->output);
		printf("%ld\tPhilo %d %s\n",
			ft_get_cur_time() - philo->all->args->start_time,
			philo->philo_id, str);
		sem_post(philo->all->sems->output);
	}
}

void	my_sleep(long time_to_wait, t_philo *philo)
{
	long	cur_time;
	long	period_of_time;

	cur_time = ft_get_cur_time();
	period_of_time = ft_get_cur_time() + time_to_wait;
	while (period_of_time > cur_time && philo->dead_flag == 0)
	{
		usleep(100);
		cur_time = ft_get_cur_time();
	}
}

int	eating(t_philo *philo)
{
	if (philo->dead_flag == 0)
	{
		sem_wait(philo->all->sems->fork);
		print_message(YELLOW"has taken a fork"RESET, philo);
	}
	return (SUCCESS);
}
