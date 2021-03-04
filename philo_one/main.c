#include "philo_one.h"

// void	putdown(t_fork *left, t_philo *p, t_fork *right)
// {
// 	pthread_mutex_lock(&(right->mutex));
// 	pthread_mutex_lock(&(left->mutex));
// 	if (left->status == 1 && right->status == 1)
// 	{
// 		left->status = 0;
// 		p->left = 0;


// 	}
// 	pthread_mutex_unlock(&(right->mutex));
// 	pthread_mutex_unlock(&(left->mutex));
// 	// 홀수면 왼쪽 들고 짝수면 오른쪽 들고
// 	if (p->index % 2)
// 	{
// 		pthread_mutex_lock(&(right->mutex));
// 		if (right->status == 0)
// 		{
// 			right->status = 1;
// 			p->right = 1;
// 		}
// 		pthread_mutex_unlock(&(right->mutex));
// 		pthread_mutex_lock(&(left->mutex));
// 		if (right->status == 1 && left->status == 0)
// 		{
// 			left->status = 1;
// 			p->left = 1;
// 		}
// 		pthread_mutex_unlock(&(left->mutex));
// 	}
// 	else
// 	{
// 		pthread_mutex_lock(&(left->mutex));
// 		if (left->status == 0)
// 		{
// 			left->status = 1;
// 			p->left = 1;
// 		}
// 		pthread_mutex_unlock(&(left->mutex));
// 		pthread_mutex_lock(&(right->mutex));
// 		if (left->status == 1 && right->status == 0)
// 		{
// 			right->status = 1;
// 			p->right = 1;
// 		}
// 		pthread_mutex_unlock(&(right->mutex));
// 	}
// }

void	eating(t_philo *p)
{
	if (p->left->status == 1 && p->right->status == 1)
	{
		pthread_mutex_lock(&(g_table.status));
		printf("timestamp_in_ms %d is eating\n", p->index); // 뮤텍스 걸어야할듯
		pthread_mutex_unlock(&(g_table.status));
	}
}

void	pickup(t_philo *p)
{
	// 홀수면 왼쪽 들고 짝수면 오른쪽 들고
	if (p->index % 2)
	{
		// 왼쪽
		pthread_mutex_lock(&(p->left->mutex));
		if (p->left->status == 0)
		{
			p->left->status = 1;
			printf("philo %d picked left\n", p->index);
		}
		pthread_mutex_unlock(&(p->left->mutex));

		// 오른쪽
		pthread_mutex_lock(&(p->right->mutex));
		if (p->left->status == 1 && p->right->status == 0)
		{
			p->right->status = 1;
			printf("philo %d picked right\n", p->index);
		}
		pthread_mutex_unlock(&(p->right->mutex));
	}
	else
	{
		// 오른쪽
		pthread_mutex_lock(&(p->right->mutex));
		if (p->right->status == 0)
		{
			p->right->status = 1;
			printf("philo %d picked right\n", p->index);
		}
		pthread_mutex_unlock(&(p->right->mutex));

		// 왼쪽
		pthread_mutex_lock(&(p->left->mutex));
		if (p->right->status == 1 && p->left->status == 0)
		{
			p->left->status = 1;
			printf("philo %d picked left\n", p->index);
		}
		pthread_mutex_unlock(&(p->left->mutex));
	}
}

void	*lifecycle(void	*philo)
{
	t_philo *p;

	p = philo;

	while (1)
	{
		pickup(p);
		eating(p);
	// 	putdown(&(g_table.f[left]), p, &(g_table.f[right]));
	// // // 	// sleeping();
	// // // 	// thinking();
	// // // 	if (p->dead)
	// // // 	{
	// // // 		printf("phillo %d -> died\n", p->index);
	// // // 		break ;
	// // // 	}

	}
	return (0);
}

void	destroy_philo(t_philo *p)
{
	int i;

	i = 0;
	while (i < g_table.number_of_philosophers)
	{
		pthread_join(p[i].thread, NULL);
		i++;
	}
	free(p);
	p = NULL;
}

void	destroy_table(t_table *table)
{
	int i;

	pthread_mutex_destroy(&(g_table.status));
	i = 0;
	while (i < table->number_of_philosophers)
	{
		pthread_mutex_destroy(&(table->f[i].mutex));
		i++;
	}
	free(table->f);
}

void	init_table(t_table *table, int argc, char *argv[])
{
	int	i;

	table->number_of_philosophers = ft_atoi(argv[1]);
	table->time_to_die = ft_atoi(argv[2]);
	table->time_to_eat = ft_atoi(argv[3]);
	table->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		table->number_of_times_each_philosopher_must_eat = ft_atoi(argv[5]);
	else
		table->number_of_times_each_philosopher_must_eat = -1;
	table->f = ft_calloc(table->number_of_philosophers, sizeof(t_fork));
	i = 0;
	while (i < table->number_of_philosophers)
	{
		pthread_mutex_init(&(table->f[i].mutex), NULL);

		i++;
	}
	pthread_mutex_init(&(g_table.status), NULL);
}

int		main(int argc, char *argv[])
{
	t_philo	*p;
	int		i;

	if (!(argc == 5 || argc == 6))
	{
		write(2, "error\n", 6);
		return (1);
	}
	init_table(&g_table, argc, argv);
	p = ft_calloc(g_table.number_of_philosophers, sizeof(t_philo));
	i = 0;
	while (i < g_table.number_of_philosophers)
	{
		p[i].index = i;

		// printf("left : %d ", p[i].index);
		p[i].left = &g_table.f[p[i].index];

		// printf("index : %d ", i);

		// printf("right : %d\n", (p[i].index + 1) % g_table.number_of_philosophers);
		p[i].right = &g_table.f[(p[i].index + 1) % g_table.number_of_philosophers];

		pthread_create(&(p[i].thread), NULL, lifecycle, &p[i]);
		i++;
	}
	destroy_philo(p);
	destroy_table(&g_table);
	return (0);
}
