/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_two.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ykoh <ykoh@student.42seoul.kr>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/15 07:18:11 by ykoh              #+#    #+#             */
/*   Updated: 2021/03/15 07:18:12 by ykoh             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_TWO_H
# define PHILO_TWO_H

# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <semaphore.h>

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
}					t_table;

typedef struct		s_philo {
	int				index;
	int				cnt;
	time_t			eat_time;
	pthread_t		thread;
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
