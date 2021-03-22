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

	i = 0;
	while (i < g_table.number_of_philosophers)
	{
		sem_post(g_table.sem);
		kill(p[i].pid, SIGKILL);
		i++;
	}
	free(p);
	p = NULL;
	sem_close(g_table.sem);
	sem_unlink("/sem");
	sem_close(g_table.print);
	sem_unlink("/print");
	sem_close(g_table.forks);
	sem_unlink("/forks");
}

static void		init_semaphore(void)
{
	sem_unlink("/forks");
	g_table.forks = sem_open("/forks", O_CREAT | O_EXCL, 0777,
									g_table.number_of_philosophers);
	sem_unlink("/print");
	g_table.print = sem_open("/print", O_CREAT | O_EXCL, 0777, 1);
	sem_unlink("/sem");
	g_table.sem = sem_open("/sem", O_CREAT | O_EXCL, 0777, 0);
}

static int		init_table(int argc, char *argv[])
{
	if (!(argc == 5 || argc == 6))
		return (0);
	if ((g_table.number_of_philosophers = ft_atoi(argv[1])) < 2 ||
		(g_table.time_to_die = ft_atoi(argv[2])) <= 0 ||
		(g_table.time_to_eat = ft_atoi(argv[3])) <= 0 ||
		(g_table.time_to_sleep = ft_atoi(argv[4])) <= 0)
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
		return (write(2, "Error\n", 6));
	p = ft_calloc(g_table.number_of_philosophers, sizeof(t_philo));
	i = 0;
	while (i < g_table.number_of_philosophers)
	{
		p[i].index = i;
		p[i].eat_time = g_table.genesis;
		if ((p[i].pid = fork()) < 0)
			return (write(2, "Error\n", 6));
		else if (p[i].pid == 0)
			break ;
		i++;
	}
	if (i != g_table.number_of_philosophers)
		lifecycle(&p[i]);
	else
		check_processes(p);
	destroy(p);
	return (0);
}
