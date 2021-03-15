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

#include "philo_two.h"

static int	dead(void)
{
	sem_post(g_table.forks);
	sem_post(g_table.forks);
	return (DEAD);
}

static int	eating(t_philo *p)
{
	sem_wait(g_table.forks);
	if (print_status(p, TAKING) == DEAD)
		return (dead());
	sem_wait(g_table.forks);
	if (print_status(p, TAKING) == DEAD)
		return (dead());
	p->eat_time = get_time();
	if (print_status(p, EATING) == DEAD)
		return (dead());
	p->cnt++;
	ft_msleep(g_table.time_to_eat);
	sem_post(g_table.forks);
	sem_post(g_table.forks);
	return (0);
}

void		*lifecycle(void *arg)
{
	t_philo				*p;

	p = arg;
	if (p->index % 2)
		ft_msleep(DELAY);
	while (1)
	{
		if (g_table.end)
			return (0);
		if (eating(p) == DEAD)
			return (0);
		if (print_status(p, SLEEPING) == DEAD)
			return (0);
		ft_msleep(g_table.time_to_sleep);
		if (print_status(p, THINKING) == DEAD)
			return (0);
	}
	return (0);
}
