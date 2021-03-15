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

#include "philo_three.h"

void	print_status(t_philo *p, int status)
{
	sem_wait(g_table.print);
	if (status == DEAD)
	{
		printf("%19ldms %10d died\n", get_time() - g_table.genesis, p->index + 1);
		exit(DEAD);
	}
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
	sem_post(g_table.print);
}
