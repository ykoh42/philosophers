/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykoh <ykoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 05:43:44 by ykoh              #+#    #+#             */
/*   Updated: 2021/03/15 05:43:45 by ykoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_one.h"

static void		destroy(t_fork *f, t_philo *p)
{
	int	i;

	i = 0;
	while (i < g_table.number_of_philosophers)
	{
		pthread_join(p[i].thread, NULL);
		i++;
	}
	free(p);
	p = NULL;
	i = 0;
	while (i < g_table.number_of_philosophers)
	{
		pthread_mutex_destroy(&(f[i].mutex));
		i++;
	}
	free(f);
	f = NULL;
	pthread_mutex_destroy(&(g_table.print));
}

static t_philo	*init_philo(t_fork *f)
{
	int		i;
	t_philo	*p;

	p = ft_calloc(g_table.number_of_philosophers, sizeof(t_philo));
	i = 0;
	while (i < g_table.number_of_philosophers)
	{
		p[i].index = i;
		p[i].eat_time = g_table.genesis;
		p[i].left = &f[i];
		if (i != (i + 1) % g_table.number_of_philosophers)
			p[i].right = &f[(i + 1) % g_table.number_of_philosophers];
		i++;
	}
	return (p);
}

static t_fork	*init_fork(void)
{
	int				i;
	t_fork			*f;

	f = ft_calloc(g_table.number_of_philosophers, sizeof(t_fork));
	i = 0;
	while (i < g_table.number_of_philosophers)
	{
		pthread_mutex_init(&(f[i].mutex), NULL);
		i++;
	}
	return (f);
}

static int		init_table(int argc, char *argv[])
{
	if (!(argc == 5 || argc == 6))
		return (0);
	if ((g_table.number_of_philosophers = ft_atoi(argv[1])) < 2 ||
		(g_table.time_to_die = ft_atoi(argv[2])) < 0 ||
		(g_table.time_to_eat = ft_atoi(argv[3])) < 0 ||
		(g_table.time_to_sleep = ft_atoi(argv[4])) < 0)
		return (0);
	if (argv[5])
	{
		if ((g_table.number_of_times_each_philosopher_must_eat =\
			ft_atoi(argv[5])) < 1)
			return (0);
	}
	g_table.genesis = get_time();
	pthread_mutex_init(&(g_table.print), NULL);
	return (1);
}

int				main(int argc, char *argv[])
{
	int				i;
	t_fork			*f;
	t_philo			*p;

	if (!init_table(argc, argv))
	{
		write(2, "Error\n", 6);
		return (1);
	}
	f = init_fork();
	p = init_philo(f);
	i = 0;
	while (i < g_table.number_of_philosophers)
	{
		pthread_create(&(p[i].thread), NULL, lifecycle, &p[i]);
		i++;
	}
	dead_or_alive(p);
	destroy(f, p);
	return (0);
}
