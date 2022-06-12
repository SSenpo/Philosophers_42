/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmago <mmago@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 16:39:48 by mmago             #+#    #+#             */
/*   Updated: 2022/06/12 22:18:09 by mmago            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	ft_free(t_all *all)
{
	sem_unlink("output");
	sem_unlink("forks");
	if (all->sems->output)
		sem_close(all->sems->output);
	if (all->sems->fork)
		sem_close(all->sems->fork);
	if (all->philo)
		free(all->philo);
	// if (all->mutex)
	// 	free(all->mutex);
	if (all->args)
		free(all->args);
	return (SUCCESS);
}

// int	death_checker(t_philo *philo)
// {
// 	long	hunger_time;

// 	// pthread_mutex_lock(&philo->all->mutex->data_race);
// 	hunger_time = ft_get_cur_time() - philo->last_eat_time;
// 	// pthread_mutex_unlock(&philo->all->mutex->data_race);
// 	if ((philo->all->args->time_die < hunger_time))
// 	{
// 		// pthread_mutex_lock(&philo->all->mutex->output);
// 		printf(RED"%ld\tPhilo %d is DIED\n"RESET,
// 			ft_get_cur_time() - philo->all->args->start_time, philo->philo_id);
// 		// pthread_mutex_lock(&philo->all->mutex->death_race);
// 		philo->all->args->flag = 1;
// 		// pthread_mutex_unlock(&philo->all->mutex->death_race);
// 		return (FAIL);
// 	}
// 	return (SUCCESS);
// }

int	ft_error(int c)
{
	if (c == 0)
		printf(RED"%s"RED, ERROR_PID);
	if (c == 1)
		printf(RED"%s"RED, ERROR_INP_ARG);
	if (c == 2)
		printf(RED"%s"RED, ERROR_NUM_ARG);
	if (c == 3)
		printf(RED"%s"RED, ERROR_MALLOC);
	return (FAIL);
}

int	ft_atoi(const char *str)
{
	int			i;
	long		num;

	i = 0;
	num = 0;
	while (str[i] == ' ' || str[i] == '\n' || str[i] == '\t'
		|| str[i] == '\v' || str[i] == '\f' || str[i] == '\r'
		|| str[i] == '-' || str[i] == '+')
		i++;
	if (!str[i])
	{
		ft_error(1);
		return (ERROR);
	}
	while (str[i] && str[i] >= '0' && str[i] <= '9')
		num = (num * 10) + (str[i++] - '0');
	if (str[i] != '\0' || num > 2147483647)
	{
		ft_error(1);
		return (ERROR);
	}
	return (num);
}

long	ft_get_cur_time(void)
{
	struct timeval	time;
	long			res;

	gettimeofday(&time, NULL);
	res = time.tv_sec * 1000 + time.tv_usec / 1000;
	return (res);
}
