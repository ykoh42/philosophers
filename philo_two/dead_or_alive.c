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

#include "philo_two.h"

static int	is_finish(int *finish)
{
	int	i;

	i = 0;
	while (i < g_table.number_of_philosophers)
	{
		if (finish[i] == 0)
			return (0);
		i++;
	}
	return (1);
}

static int	is_dead(t_philo *p)
{
	const time_t	timestamp = get_time();

	if (g_table.time_to_die <= timestamp - p->eat_time)
	{
		print_status(p, DEAD);
		return (1);
	}
	return (0);
}

void		dead_or_alive(void *arg)
{
	t_philo	*p;
	int		*finish;
	int		i;

	p = arg;
	finish = ft_calloc(g_table.number_of_philosophers, sizeof(int));
	i = 0;
	while (1)
	{
		if (i == g_table.number_of_philosophers)
			i = 0;
		if (is_dead(&p[i]))
			break ;
		if (g_table.number_of_times_each_philosopher_must_eat &&
			p[i].cnt >= g_table.number_of_times_each_philosopher_must_eat)
			finish[i] = 1;
		if (is_finish(finish))
		{
			print_status(NULL, END);
			break ;
		}
		usleep(100);
		i++;
	}
	free(finish);
}
