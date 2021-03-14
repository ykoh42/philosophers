#include "philo_one.h"

int	print_status(t_philo *p, int status)
{
	pthread_mutex_lock((&g_table.print));
	if (g_table.end)
	{
		pthread_mutex_unlock((&g_table.print));
		return (DEAD);
	}
	if (status == DEAD || status == END)
	{
		g_table.end = 1;
		if (status == DEAD)
			printf("%19ldms %10d died\n", get_time() - g_table.genesis, p->index + 1);
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
	pthread_mutex_unlock((&g_table.print));
	return ((status == END) ? DEAD : status);
}

// int	print_status(t_philo *p, int status)
// {
// 	pthread_mutex_lock((&g_table.print));
// 	if (g_table.end)
// 	{
// 		pthread_mutex_unlock((&g_table.print));
// 		return (DEAD);
// 	}
// 	if (status == DEAD || status == END)
// 	{
// 		g_table.end = 1;
// 		if (status == DEAD)
// 			printf("%19ldms %10d died\n", get_time() - g_table.genesis, p->index + 1);
// 	}
// 	else if (status == LEFTTAKING)
// 		printf("%19ldms %10d has taken a  left fork\n", get_time() - g_table.genesis, p->index + 1);
// 	else if (status == RIGHTTAKING)
// 		printf("%19ldms %10d has taken a right fork\n", get_time() - g_table.genesis, p->index + 1);
// 	else if (status == TAKING)
// 		printf("%19ldms %10d has taken a fork\n", get_time() - g_table.genesis, p->index + 1);
// 	else if (status == EATING)
// 		printf("%19ldms %10d is eating\n", get_time() - g_table.genesis, p->index + 1);
// 	else if (status == SLEEPING)
// 		printf("%19ldms %10d is sleeping\n", get_time() - g_table.genesis, p->index + 1);
// 	else if (status == THINKING)
// 		printf("%19ldms %10d is thinking\n", get_time() - g_table.genesis, p->index + 1);
// 	pthread_mutex_unlock((&g_table.print));
// 	return ((status == END) ? DEAD : status);
// }

