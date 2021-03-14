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

#include "philo_one.h"

static int	dead(t_philo *p)
{
	pthread_mutex_unlock(&(p->left->mutex));
	pthread_mutex_unlock(&(p->right->mutex));
	return (DEAD);
}

static int	eating(t_philo *p)
{
	pthread_mutex_lock(&(p->left->mutex));
	p->left->status = 1;
	if (print_status(p, LEFTTAKING) == DEAD)
		return (dead(p));
	pthread_mutex_lock(&(p->right->mutex));
	p->right->status = 1;
	if (print_status(p, RIGHTTAKING) == DEAD)
		return (dead(p));
	p->eat_time = get_time();
	if (print_status(p, EATING) == DEAD)
		return (dead(p));
	p->cnt++;
	ft_msleep(g_table.time_to_eat);
	p->left->status = 0;
	p->right->status = 0;
	pthread_mutex_unlock(&(p->right->mutex));
	pthread_mutex_unlock(&(p->left->mutex));
	return (0);
}

void		*lifecycle(void *arg)
{
	t_philo				*p;

	p = arg;
	if (!(p->index % 2))
		ft_msleep(1);
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
