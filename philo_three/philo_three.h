
#ifndef PHILO_THREE_H
# define PHILO_THREE_H

# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <semaphore.h>
# include <signal.h>

enum				e_status {
	INIT,
	LEFTTAKING,
	RIGHTTAKING,
	TAKING,
	THINKING,
	EATING,
	SLEEPING,
	DEAD,
	END
};

typedef struct		s_table {
	int				number_of_philosophers;
	time_t			time_to_die;
	time_t			time_to_eat;
	time_t			time_to_sleep;
	int				number_of_times_each_philosopher_must_eat;
	int				end;
	time_t			genesis;
	sem_t			*the_same_time;
	sem_t			*forks;
	sem_t			*print;
	sem_t			*sem;
}					t_table;

typedef struct		s_philo {
	int				index;
	int				cnt;
	time_t			eat_time;
	pid_t			pid;
}					t_philo;

t_table				g_table;

int					ft_atoi(const char *str);
void				*ft_calloc(size_t count, size_t size);
void				ft_msleep(time_t millisecond);
time_t				get_time(void);
void				lifecycle(t_philo *p);
void				print_status(t_philo *p, int status);
char				*get_name(int n);
void				destroy(t_philo *p);
void				check_processes(t_philo *p);
#endif
