/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmago <mmago@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 16:39:53 by mmago             #+#    #+#             */
/*   Updated: 2022/06/13 17:33:58 by mmago            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	*ft_try(void *data)
{
	t_philo		*philo;

	philo = (t_philo *)data;
	pthread_detach(philo->thread_id);
	get_last_meal(philo);
	while (1)
	{
		print_message(BLUE"is thinking"RESET, philo);
		eating(philo);
		get_last_meal(philo);
		my_sleep(philo->all->args->time_eat, philo);
		pthread_mutex_unlock(philo->right_id);
		pthread_mutex_unlock(philo->left_id);
		if (++philo->count_eat == philo->all->args->must_eat)
		{
			pthread_mutex_lock(&philo->all->mutex->data_race);
			philo->dead_flag = 1;
			pthread_mutex_unlock(&philo->all->mutex->data_race);
		}
		print_message(MAGENTA"is sleeping"RESET, philo);
		my_sleep(philo->all->args->time_sleep, philo);
	}
	return (SUCCESS);
}

void	*ft_check_end(void *data)
{
	t_all	*all;

	all = (t_all *)data;
	while (1)
	{
		pthread_mutex_lock(&all->mutex->death_race);
		if (all->args->flag == 0)
		{
			pthread_mutex_unlock(&all->mutex->death_race);
			check_end_two(all);
		}
		else
		{
			pthread_mutex_unlock(&all->mutex->death_race);
			break ;
		}
	}
	usleep(331);
	return (SUCCESS);
}

void	ft_thread_init(t_all *all)
{
	int	i;

	i = 0;
	all->args->start_time = ft_get_cur_time();
	while (i < all->args->num_ph)
	{
		if (all->philo[i].philo_id % 2 == 0)
		{
			pthread_create(&all->philo[i].thread_id, NULL,
				&ft_try, &all->philo[i]);
		}
		if (all->philo[i].philo_id % 2 == 1)
		{
			pthread_create(&all->philo[i].thread_id, NULL,
				&ft_try, &all->philo[i]);
		}
		i++;
		usleep(30);
	}
	pthread_create(&all->end, NULL, &ft_check_end, all);
	pthread_join(all->end, NULL);
	ft_free(all);
}

int	ft_mutex_init(t_all *all)
{
	int	i;

	i = 0;
	all->mutex = malloc(sizeof(t_mutex));
	all->mutex->fork = malloc(sizeof(pthread_mutex_t) * all->args->num_ph);
	while (i < all->args->num_ph)
	{
		if (pthread_mutex_init(&all->mutex->fork[i], NULL))
			return (ERROR_MUTEX_INT);
		i++;
	}
	if (pthread_mutex_init(&all->mutex->output, NULL))
		return (ERROR_MUTEX_INT);
	if (pthread_mutex_init(&all->mutex->data_race, NULL))
		return (ERROR_MUTEX_INT);
	if (pthread_mutex_init(&all->mutex->death_race, NULL))
		return (ERROR_MUTEX_INT);
	return (SUCCESS);
}

int	ft_init_philos(t_all *all)
{
	int		i;

	i = 0;
	all->philo = malloc(sizeof(t_philo) * all->args->num_ph);
	if (!all->philo)
		return (FAIL);
	ft_mutex_init(all);
	if (all->args->num_ph == 0)
		return (FAIL);
	while (i < all->args->num_ph)
	{
		all->philo[i].philo_id = i + 1;
		all->philo[i].dead_flag = 0;
		all->philo[i].left_id = &all->mutex->fork[(i + 1) % all->args->num_ph];
		all->philo[i].right_id = &all->mutex->fork[i];
		all->philo[i].count_eat = 0;
		all->philo[i].all = all;
		i++;
	}
	ft_thread_init(all);
	return (SUCCESS);
}
