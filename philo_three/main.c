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

#include "philo_three.h"

void			destroy(t_philo *p)
{
	int		i;
	char	*name;

	i = 0;
	while (i < g_table.number_of_philosophers)
		kill(p[i++].pid, SIGKILL);
	free(p);
	p = NULL;
	i = 0;
	while (i < g_table.number_of_philosophers)
	{
		name = get_name(i);
		sem_unlink(name);
		g_table.sem[i] = sem_open(name, O_CREAT | O_EXCL, 0755, 1);
		sem_post(g_table.sem[i]);
		free(name);
		i++;
	}
	free(g_table.sem);
	sem_close(g_table.print);
	sem_unlink("/print");
	sem_close(g_table.forks);
	sem_unlink("/forks");
	sem_close(g_table.the_same_time);
	sem_unlink("/the_same_time");
}

static void		init_semaphore(void)
{
	int		i;
	char	*name;

	sem_unlink("/the_same_time");
	g_table.the_same_time = sem_open("/the_same_time", O_CREAT | O_EXCL, 0755,
									g_table.number_of_philosophers / 2);
	sem_unlink("/forks");
	g_table.forks = sem_open("/forks", O_CREAT | O_EXCL, 0755,
									g_table.number_of_philosophers);
	sem_unlink("/print");
	g_table.print = sem_open("/print", O_CREAT | O_EXCL, 0755, 1);
	g_table.sem = ft_calloc(g_table.number_of_philosophers, sizeof(sem_t *));
	i = 0;
	while (i < g_table.number_of_philosophers)
	{
		name = get_name(i);
		sem_unlink(name);
		g_table.sem[i] = sem_open(name, O_CREAT | O_EXCL, 0755, 1);
		sem_wait(g_table.sem[i]); // warning
		free(name);
		i++;
	}
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
	init_semaphore();
	return (1);
}

int				main(int argc, char *argv[])
{
	int				i;
	t_philo			*p;

	if (!init_table(argc, argv))
	{
		write(2, "error\n", 6);
		return (1);
	}
	p = ft_calloc(g_table.number_of_philosophers, sizeof(t_philo));
	i = 0;
	while (i < g_table.number_of_philosophers)
	{
		p[i].index = i;
		p[i].eat_time = g_table.genesis;
		if ((p[i].pid = fork()) < 0)
		{
			write(2, "error\n", 6);
			return (1);
		}
		else if (p[i].pid == 0)
			break ;
		i++;
	}
	if (i != g_table.number_of_philosophers)
		lifecycle(&p[i]);
	else
		dead_or_alive(p);
	destroy(p);
	return (0);
}
