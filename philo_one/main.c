#include "philo_one.h"

// 인수 처리
// 철학자 생성
// 포크 생성

// 작업 수행
// 	포크집기
// 	먹기
// 	자기
//	생각하기

// 포크 제거
// 철학자 제거
// 종료

static void	*pickup(void *param)
{
	int	i;

	i = 1;
	while (i < ((t_data *)param)->number_of_philosophers)
	{
		pthread_mutex_lock();

		i++;
	}

}

static void	destroy(t_data *param)
{
	int	i;

	i = 1;
	while (i <= param->number_of_philosophers)
	{
		// 스레드 해제 추가
		pthread_join(param->p[i].thread, NULL); // join 이랑 detach 차이 모르겟음
		// 뮤텍스 해제 추가
		pthread_mutex_destroy(param->f[i].mutex);

		i++;
	}

	free(param->p);
	free(param->f);
}

static void	init(t_data *param, int argc, char *argv[])
{
	int	i;

	param->number_of_philosophers = ft_atoi(argv[1]);
	param->time_to_die = ft_atoi(argv[2]);
	param->time_to_eat = ft_atoi(argv[3]);
	param->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		param->number_of_times_each_philosopher_must_eat = ft_atoi(argv[5]);
	param->p = ft_calloc(param->number_of_philosophers + 2, sizeof(t_philo));
	param->f = ft_calloc(param->number_of_philosophers + 2, sizeof(t_fork));
	i = 1;
	while (i <= param->number_of_philosophers)
	{
		pthread_create(param->p[i].thread, NULL, pickup, param);
		pthread_mutex_init(param->f[i].mutex, NULL);
		i++;
	}
}

int			main(int argc, char *argv[])
{
	t_data	param;

	if (argc == 5 || argc == 6)
	{
		init(&param, argc, argv);




		destroy(&param);
	}
	return (0);
}