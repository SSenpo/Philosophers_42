/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmago <mmago@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 16:39:53 by mmago             #+#    #+#             */
/*   Updated: 2022/06/13 20:37:08 by mmago            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	ft_try(t_philo *philo)
{
	ft_create_check_thread(philo);
	while (philo->all->args->num_ph < 2 && philo->dead_flag == 0)
		my_sleep(50, philo);
	while (philo->dead_flag == 0)
	{
		print_message(BLUE"is thinking"RESET, philo);
		eating(philo);
		get_last_meal(philo);
		print_message(CYAN"is eating"RESET, philo);
		my_sleep(philo->all->args->time_eat, philo);
		sem_post(philo->all->sems->fork);
		if ((++philo->count_eat == philo->all->args->must_eat)
			&& philo->dead_flag == 0)
			exit(0);
		if (philo->dead_flag == 0)
		{
			print_message(MAGENTA"is sleeping"RESET, philo);
			my_sleep(philo->all->args->time_sleep, philo);
		}
	}
}

void	*ft_check_end(void *data)
{
	t_all	*all;
	long	hunger_time;

	all = (t_all *)data;
	while (1)
	{
		hunger_time = ft_get_cur_time() - all->philo->last_eat_time;
		if (all->args->time_die < hunger_time)
		{
			sem_wait(all->sems->output);
			printf(RED"%ld\tPhilo %d is DIED\n"RESET, ft_get_cur_time()
				- all->args->start_time, all->philo->philo_id);
			all->philo->dead_flag = 1;
			exit(1);
		}
	}
	return (SUCCESS);
}

int	ft_init_procces(t_all *all)
{
	int	i;

	i = 0;
	all->args->start_time = ft_get_cur_time();
	while (i < all->args->num_ph)
	{
		all->philo->pid[i] = fork();
		if (!all->philo->pid[i])
		{
			all->philo->philo_id = i + 1;
			ft_try(all->philo);
		}
		else if (all->philo->pid[i] < 0)
			return (FAIL);
		i++;
	}
	ft_wait(all);
	return (ft_free(all));
}

int	ft_sem_init(t_all *all)
{
	all->sems = malloc(sizeof(t_sema));
	if (!all->sems)
		return (FAIL);
	sem_unlink("output");
	all->sems->output = sem_open("output", O_CREAT, 0644, 1);
	if (all->sems->output == SEM_FAILED)
		return (ERROR_SEMOPEN_INT);
	sem_unlink("fork");
	all->sems->fork = sem_open("fork", O_CREAT, 0644,
			all->args->num_ph / 2);
	if (all->sems->fork == SEM_FAILED)
		return (ERROR_SEMOPEN_INT);
	return (SUCCESS);
}

int	ft_init_philos(t_all *all)
{
	all->philo = malloc(sizeof(t_philo));
	if (!all->philo)
		return (FAIL);
	all->philo->pid = malloc(sizeof(pid_t) * all->args->num_ph);
	if (!all->philo->pid)
		return (FAIL);
	all->philo->dead_flag = 0;
	all->philo->count_eat = 0;
	all->philo->all = all;
	ft_sem_init(all);
	ft_init_procces(all);
	return (SUCCESS);
}
