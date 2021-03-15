/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dead_or_alive.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykoh <ykoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 05:47:06 by ykoh              #+#    #+#             */
/*   Updated: 2021/03/15 05:47:07 by ykoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

static void	*is_dead(void *arg)
{
	t_philo	*p;
	int		i;
	int		exit_status;

	p = arg;
	i = 0;
	while (1)
	{
		if (i == g_table.number_of_philosophers)
			i = 0;
		if (g_table.end)
			return (0);
		if (p[i].pid == waitpid(p[i].pid, &exit_status, WNOHANG))
		{
			if (exit_status / 256 == DEAD)
			{
				destroy(p);
				exit(0);
			}
		}
		usleep(USLEEP);
		i++;
	}
	return (0);
}

void		check_processes(t_philo *p)
{
	pthread_t	th;
	int			i;

	pthread_create(&th, NULL, is_dead, p);
	if (g_table.number_of_times_each_philosopher_must_eat)
	{
		i = 0;
		while (i < g_table.number_of_philosophers)
		{
			sem_wait(g_table.sem);
			i++;
		}
		g_table.end = 1;
		pthread_join(th, NULL);
		destroy(p);
		exit(0);
	}
	pthread_join(th, NULL);
}
