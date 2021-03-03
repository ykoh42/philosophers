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

typedef struct	s_philo {
	pthread_t 	*thread;
	int			left;
	int			right;
	int			status;
}				t_philo;

typedef struct	s_fork {
	// 포인터 붙여야하나..?
	pthread_mutex_t		*mutex;
	int					status;
}				t_fork;

typedef struct	s_data {
	int			number_of_philosophers;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			number_of_times_each_philosopher_must_eat;
	t_philo		*p;
	t_fork		*f;
}				t_data;



int				ft_atoi(const char *str);
void			*ft_calloc(size_t count, size_t size);
#endif
