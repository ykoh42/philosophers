/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykoh <ykoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/03 19:57:19 by ykoh              #+#    #+#             */
/*   Updated: 2020/05/05 00:58:23 by ykoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>

static int	ft_isspace(int c)
{
	return ((c >= 9 && c <= 13) || c == 32);
}

static int	ft_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

int			ft_atoi(const char *str)
{
	char				neg;
	unsigned long long	num;

	while (ft_isspace(*str))
		str++;
	neg = (*str == '-');
	if (*str == '+' || *str == '-')
		str++;
	num = 0;
	while (ft_isdigit(*str))
	{
		num = num * 10 + (*str - '0');
		str++;
	}
	if (num > LONG_MAX - 1 && neg == 1)
		return (0);
	if (num > LONG_MAX && neg == 0)
		return (-1);
	return (neg ? -num : num);
}
