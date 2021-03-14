/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_status.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykoh <ykoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 06:08:05 by ykoh              #+#    #+#             */
/*   Updated: 2021/03/15 06:08:06 by ykoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

static int	end_status(void)
{
	g_table.end = 1;
	pthread_mutex_unlock((&g_table.print));
	return (DEAD);
}

static int	dead_status(t_philo *p)
{
	g_table.end = 1;
	printf("%19ldms %10d died\n", get_time() - g_table.genesis, p->index + 1);
	pthread_mutex_unlock((&g_table.print));
	return (DEAD);
}

int			print_status(t_philo *p, int status)
{
	pthread_mutex_lock((&g_table.print));
	if (g_table.end)
	{
		pthread_mutex_unlock((&g_table.print));
		return (DEAD);
	}
	if (status == END)
		return (end_status());
	else if (status == DEAD)
		return (dead_status(p));
	else if (status == TAKING)
		printf("%19ldms %10d has taken a fork\n",
				get_time() - g_table.genesis, p->index + 1);
	else if (status == EATING)
		printf("%19ldms %10d is eating\n",
				get_time() - g_table.genesis, p->index + 1);
	else if (status == SLEEPING)
		printf("%19ldms %10d is sleeping\n",
				get_time() - g_table.genesis, p->index + 1);
	else if (status == THINKING)
		printf("%19ldms %10d is thinking\n",
				get_time() - g_table.genesis, p->index + 1);
	pthread_mutex_unlock((&g_table.print));
	return (status);
}
