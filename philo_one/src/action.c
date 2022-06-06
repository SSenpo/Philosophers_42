/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   action.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmago <mmago@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 16:39:51 by mmago             #+#    #+#             */
/*   Updated: 2022/05/21 15:13:00 by mmago            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	check_end_two(t_all *all)
{
	int	i;
	int	end;

	i = -1;
	end = 0;
	while (++i < all->args->num_ph)
	{
		pthread_mutex_lock(&all->mutex->data_race);
		if (all->philo[i].dead_flag == 1)
			end++;
		pthread_mutex_unlock(&all->mutex->data_race);
		if (death_checker(&all->philo[i]))
			break ;
		if (end == all->args->num_ph)
		{
			pthread_mutex_lock(&all->mutex->death_race);
			all->args->flag = 1;
			pthread_mutex_unlock(&all->mutex->death_race);
			printf("Philo's are full.\n");
			break ;
		}
	}
}

void	get_last_meal(t_philo *philo)
{
	pthread_mutex_lock(&philo->all->mutex->data_race);
	philo->last_eat_time = ft_get_cur_time();
	pthread_mutex_unlock(&philo->all->mutex->data_race);
}

void	print_message(char *str, t_philo *philo)
{
	pthread_mutex_lock(&philo->all->mutex->output);
	pthread_mutex_lock(&philo->all->mutex->death_race);
	if (philo->all->args->flag == 1)
	{
		pthread_mutex_unlock(&philo->all->mutex->death_race);
		return ;
	}
	else if (philo->all->args->flag == 0)
	{
		printf("%ld\tPhilo %d %s\n",
			ft_get_cur_time() - philo->all->args->start_time,
			philo->philo_id, str);
		pthread_mutex_unlock(&philo->all->mutex->death_race);
		pthread_mutex_unlock(&philo->all->mutex->output);
	}
}

void	my_sleep(long time_to_wait, t_philo *philo)
{
	long	cur_time;
	long	period_of_time;

	cur_time = ft_get_cur_time();
	period_of_time = ft_get_cur_time() + time_to_wait;
	while (period_of_time > cur_time)
	{
		pthread_mutex_lock(&philo->all->mutex->death_race);
		if (philo->all->args->flag == 1)
		{
			pthread_mutex_unlock(&philo->all->mutex->death_race);
			return ;
		}
		pthread_mutex_unlock(&philo->all->mutex->death_race);
		usleep(100);
		cur_time = ft_get_cur_time();
	}
}

int	eating(t_philo *philo)
{
	pthread_mutex_lock(&philo->all->mutex->death_race);
	if (philo->all->args->flag == 1)
	{
		pthread_mutex_unlock(&philo->all->mutex->death_race);
		return (SUCCESS);
	}
	pthread_mutex_unlock(&philo->all->mutex->death_race);
	if (philo->philo_id % 2 == 0)
	{
		pthread_mutex_lock(philo->right_id);
		print_message(YELLOW"has taken a right fork"RESET, philo);
		pthread_mutex_lock(philo->left_id);
		print_message(YELLOW"has taken a left fork"RESET, philo);
	}
	if (philo->philo_id % 2 == 1)
	{
		pthread_mutex_lock(philo->left_id);
		print_message(YELLOW"has taken a left fork"RESET, philo);
		pthread_mutex_lock(philo->right_id);
		print_message(YELLOW"has taken a right fork"RESET, philo);
	}
	print_message(CYAN"is eating"RESET, philo);
	return (SUCCESS);
}
