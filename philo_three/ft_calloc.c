/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykoh <ykoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/09 00:56:57 by ykoh              #+#    #+#             */
/*   Updated: 2020/04/09 21:00:20 by ykoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <string.h>

static void	ft_bzero(void *s, size_t n)
{
	memset(s, 0x00, n);
}

void		*ft_calloc(size_t count, size_t size)
{
	const size_t	mem = count * size;
	void			*p;

	if (!(p = malloc(mem)))
		return (NULL);
	ft_bzero(p, mem);
	return (p);
}
