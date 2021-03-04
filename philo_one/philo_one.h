#ifndef PHILO_ONE_H
# define PHILO_ONE_H

# include <stdio.h>

# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

enum			e_status {
	EATING,
	THINKING,
	SLEEPING
};

typedef struct			s_fork {
	pthread_mutex_t		mutex;
	int					status;
}						t_fork;

typedef struct			s_table {
	int					number_of_philosophers;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					number_of_times_each_philosopher_must_eat;
	t_fork				*f;
	pthread_mutex_t		status;
}						t_table;

typedef struct	s_philo {
	int			index;
	pthread_t 	thread;
	t_fork		*left;
	t_fork		*right;
	int			status;
	int			dead;
}				t_philo;

t_table			g_table;

int				ft_atoi(const char *str);
void			*ft_calloc(size_t count, size_t size);
#endif
