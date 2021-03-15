/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykoh <ykoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 06:09:31 by ykoh              #+#    #+#             */
/*   Updated: 2021/03/15 06:09:32 by ykoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_ONE_H
# define PHILO_ONE_H

# define USLEEP 100
# define DELAY 5

# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>

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
	pthread_mutex_t	print;
}					t_table;

typedef struct		s_fork {
	pthread_mutex_t	mutex;
	int				status;
}					t_fork;

typedef struct		s_philo {
	int				index;
	int				cnt;
	time_t			eat_time;
	pthread_t		thread;
	t_fork			*left;
	t_fork			*right;
}					t_philo;

t_table				g_table;

int					ft_atoi(const char *str);
void				*ft_calloc(size_t count, size_t size);
void				ft_msleep(time_t millisecond);
time_t				get_time(void);
void				*lifecycle(void *arg);
int					print_status(t_philo *p, int status);
void				dead_or_alive(void *arg);
#endif
