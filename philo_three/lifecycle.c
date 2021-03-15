/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lifecycle.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykoh <ykoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 05:46:37 by ykoh              #+#    #+#             */
/*   Updated: 2021/03/15 05:46:38 by ykoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

static void	eating(t_philo *p)
{
	sem_wait(g_table.forks);
	print_status(p, TAKING);
	sem_wait(g_table.forks);
	print_status(p, TAKING);
	p->eat_time = get_time();
	print_status(p, EATING);
	p->cnt++;
	if (g_table.number_of_times_each_philosopher_must_eat &&
		p->cnt == g_table.number_of_times_each_philosopher_must_eat)
		sem_post(g_table.sem);
	ft_msleep(g_table.time_to_eat);
	sem_post(g_table.forks);
	sem_post(g_table.forks);
}

static void	*dead_or_alive(void *arg)
{
	t_philo	*p;

	p = arg;
	if (p->index % 2)
		ft_msleep(DELAY);
	while (1)
	{
		if (g_table.time_to_die <= get_time() - p->eat_time)
		{
			print_status(p, DEAD);
			return (0);
		}
		usleep(USLEEP);
	}
	return (0);
}

void		lifecycle(t_philo *p)
{
	pthread_t	th;

	pthread_create(&th, NULL, dead_or_alive, p);
	while (1)
	{
		eating(p);
		print_status(p, SLEEPING);
		ft_msleep(g_table.time_to_sleep);
		print_status(p, THINKING);
	}
	pthread_join(th, NULL);
}
