/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmago <mmago@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/09 16:39:53 by mmago             #+#    #+#             */
/*   Updated: 2022/06/12 22:54:10 by mmago            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	ft_try(t_philo *philo)
{
	// get_last_meal(philo);
	philo->last_eat_time = ft_get_cur_time();
	pthread_create(&philo->all->end, NULL, ft_check_end, (void *)philo->all);
	pthread_detach(philo->all->end);
	while (philo->dead_flag == 0)
	{
		eating(philo);
		philo->last_eat_time = ft_get_cur_time();
		get_last_meal(philo);
		my_sleep(philo->all->args->time_eat);
		sem_post(philo->all->sems->fork);
		// pthread_mutex_unlock(philo->right_id);
		// pthread_mutex_unlock(philo->left_id);
		if (++philo->count_eat == philo->all->args->must_eat)
		{
			// pthread_mutex_lock(&philo->all->mutex->data_race);
			// philo->dead_flag = 1;
			exit(0);
			// pthread_mutex_unlock(&philo->all->mutex->data_race);
		}
		print_message(MAGENTA"is sleeping"RESET, philo);
		my_sleep(philo->all->args->time_sleep);
		print_message(BLUE"is thinking"RESET, philo);
	}
	exit(1);
	// exit(0);
	// return (SUCCESS);
}

void	*ft_check_end(void *data)
{
	t_all	*all;
	long	hunger_time;

	all = (t_all *)data;
	
	while (1)
	{
		hunger_time = ft_get_cur_time() - all->philo->last_eat_time;
		// pthread_mutex_lock(&all->sems->death_race);
		if (all->args->time_die < hunger_time)
		{
			sem_wait(all->sems->output);
			printf(RED"%ld\tPhilo %d is DIED\n"RESET,
			ft_get_cur_time() - all->args->start_time, all->philo->philo_id);
			all->philo->dead_flag = 1;
			break;
			// exit(1);
			// pthread_mutex_unlock(&all->mutex->death_race);
			// check_end_two(all);
		}

		// if (all->philo->dead_flag == 1)
		// {
		// 	// sem_wait(all->sems->output);
		// 	// printf("%ld\tPhilo is full\n",
		// 	// ft_get_cur_time() - all->args->start_time);
		// 	exit(0);
		// 	// pthread_mutex_unlock(&all->mutex->death_race);
		// }
	}
	return (SUCCESS);
	// usleep(331);
	// return (SUCCESS);
}

void	ft_wait(t_all *all)
{
	int	i;
	int	j;
	int	status;

	i = 0;
	while (i < all->args->num_ph)
	{
		waitpid(-1, &status, 0);
		// write(1, "S\n", 2);
		// printf("%d\n", status);
		if (status == 256)
		{
			write(1, "A\n", 2);
			j = 0;
			while (j < all->args->num_ph)
			{
				kill(all->philo->pid[j], SIGTERM);
				j++;
			}
			return ;
		}
		else if (status == 0)
			i++;
	}
	sem_wait(all->sems->output);
	printf("%ld\tPhilo is full\n",
		ft_get_cur_time() - all->args->start_time);
	return ;
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
	// sem_unlink("eat_check");
	// all->sems->eat_check = sem_open("eat_check", O_CREAT, 0644,
	// 		all->args->num_ph);
	// if (all->sems->eat_check == SEM_FAILED)
	// 	return (ERROR_SEMOPEN_INT);
	
	// all->args->start_time = ft_get_cur_time();
	// while (i < all->args->num_ph)
	// {
	// 	if (all->philo[i].philo_id % 2 == 0)
	// 	{
			
	// 	}
	// 	if (all->philo[i].philo_id % 2 == 1)
	// 	{

	// 	}
	// 	i++;
	// 	// usleep(30);
	// }
	// pthread_create(&all->end, NULL, &ft_check_end, all);
	// pthread_join(all->end, NULL);
	// ft_free(all);
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
	// all->philo[i].left_id = &all->mutex->fork[(i + 1) % all->args->num_ph];
	// all->philo[i].right_id = &all->mutex->fork[i];
	all->philo->count_eat = 0;
	all->philo->all = all;
	ft_sem_init(all);
	ft_init_procces(all);
	return (SUCCESS);
}
