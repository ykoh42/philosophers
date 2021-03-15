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
	sem_wait(g_table.the_same_time);
	sem_wait(g_table.forks);
	print_status(p, TAKING);
	print_status(p, TAKING);
	p->eat_time = get_time();
	print_status(p, EATING);
	ft_msleep(g_table.time_to_eat);
	p->cnt++;
	if (p->cnt == g_table.number_of_times_each_philosopher_must_eat)
		sem_post(g_table.sem[p->index]);
	sem_post(g_table.forks);
	sem_post(g_table.the_same_time);
}

void		lifecycle(t_philo *p)
{
	while (1)
	{
		eating(p);
		print_status(p, SLEEPING);
		ft_msleep(g_table.time_to_sleep);
		print_status(p, THINKING);
	}
}
