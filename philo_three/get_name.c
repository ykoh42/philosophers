#include "philo_three.h"

static	size_t	get_width(int n)
{
	size_t	width;

	if (n == 0)
		width = 4;
	else 
		width = 3;
	while (n)
	{
		n /= 10;
		width++;
	}
	return (width);
}

char			*get_name(int n)
{
	char			*num;
	int				rem;
	size_t			i;
	const size_t	width = get_width(n);

	if (!(num = ft_calloc(width + 1, sizeof(char))))
		return (NULL);
	num[0] = '/';
	num[1] = 'f';
	num[2] = 't';
	i = 3;
	while (i < width)
	{
		rem = n % 10;
		n = n / 10;
		num[i] = "0123456789"[rem];
		i++;
	}
	return (num);
}
