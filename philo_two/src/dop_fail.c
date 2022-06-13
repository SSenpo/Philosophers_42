/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dop_fail.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmago <mmago@student.21-school.ru>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/13 15:29:18 by mmago             #+#    #+#             */
/*   Updated: 2022/06/13 20:35:45 by mmago            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	ft_create_check_thread(t_philo *philo)
{
	philo->last_eat_time = philo->all->args->start_time;
	philo->all->end = malloc(sizeof(pthread_t));
	pthread_create(&philo->all->end, NULL, ft_check_end, (void *)philo->all);
	pthread_detach(philo->all->end);
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
		if (status == 256)
		{
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
