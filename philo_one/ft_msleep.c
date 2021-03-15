/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_msleep.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykoh <ykoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 02:56:48 by ykoh              #+#    #+#             */
/*   Updated: 2021/03/15 02:57:06 by ykoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

void	ft_msleep(time_t millisecond)
{
	const time_t	base = get_time();

	while (1)
	{
		if (millisecond < get_time() - base)
			return ;
		usleep(USLEEP);
	}
}
