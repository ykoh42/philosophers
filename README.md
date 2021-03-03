# Philosophers
> 식사하는 철학자 문제


## 주제
이 프로젝트에서는 프로세스 스레딩의 기본 사항과 동일한 메모리 공간에서 작업하는 방법을 배웁니다. 스레드를을 만드는 방법을 배웁니다. 뮤텍스, 세마포어 및 공유 메모리에 대해 배웁니다.

## 목표
`deadlock`문제를 해결하여 철학자가 굶어죽지 않는 프로그램을 작성한다.


## 문제
[식사하는 철학자 문제](https://namu.wiki/w/%EC%8B%9D%EC%82%AC%ED%95%98%EB%8A%94%20%EC%B2%A0%ED%95%99%EC%9E%90%20%EB%AC%B8%EC%A0%9C)는 `deadlock`의 대표적인 예제이며, deadklock의 4가지 발생 조건을 모두 만족한다.

### Deadlock의 4가지 발생 조건

**`Deaklock`** : 철학자가 식사를 하지 못해 굶어 죽음(Starvation)
1. Mutual Exclusion : 포크(이하 젓가락)는 한번에 한 철학자만 사용할 수 있음.
2. Hold and Wait : 집어든 젓가락을 계속 들을 채로 반대쪽 젓가락을 기다림.
3. No Preemption : 다른 철학자의 젓가락을 강제로 뺏을 수 없음.
4. Circular Wait : 모든 철학자들이 자신의 오른쪽에 앉은 철학자가 젓가락을 놓기를 기다림.

## 해결 방법
철학자는 스레드 혹은 프로세스, 젓가락은 공유 메모리(자원)을 상징한다.  
deadlock의 발생 조건 4가지 중 하나만 해결하여도 deadlock을 해결할 수 있다. 
<details>
<summary>에츠허르 데이크스트라의 해결책은 다음과 같다.</summary>
각각의 철학자를 P<sub>1</sub>, P<sub>2</sub>, P<sub>3</sub>, P<sub>4</sub>, P<sub>5</sub>라고 하고, 각 철학자의 왼쪽 포크를 f<sub>1</sub>, f<sub>2</sub>, f<sub>3</sub>, f<sub>4</sub>,f<sub>5</sub>라고 하자. P<sub>5</sub>를 제외한 네 명은 먼저 f<sub>n</sub>를 집은 후 f<sub>n+1</sub>를 집는 방식을 취한다. 그리고 P<sub>5</sub>는 이와 반대로, f<sub>1</sub>를 먼저 집은 후 f<sub>5</sub>를 집는다. 이것은 원래 방식의 대칭성을 제거하고, 따라서 교착 상태를 막을 수 있다.
</details>

## 규칙 정의
1. 철학자는 3가지 행동을 한다: 먹기, 자기, 생각하기
2. 동시에 2가지 행동을 할 수 없다.
3. 포크를 양 손에 하나씩 즉, 2개를 집어야 먹을 수 있다.
4. 철학자는 굶어 죽으면 안되고, 반드시 먹어야 한다.
5. 철학자를 서로 이야기를 하지 않으며, 누가 언제 죽을지 모른다.
6. 철학자가 잠을 다 자면, 생각하기 시작한다.
7. 아래의 프로그램들은 다음의 인자를 받을 수 있다.
	* number_of_philosophers : 철학자 수(포크 수)
	* time_to_die : 식사를 하지 않으면 죽는 시간
	* time_to_eat : 먹는데 걸리는 시간
	* time_to_sleep : 자는데 걸리는 시간
	* number_of_times_each_philosopher_must_eat(optional) : 프로그램 종료까지 반드시 먹어야 하는 횟수
8. 철학자는 원탁에 앉아 있으며, 1번부터 시작한다.
9. `N`번 철학자는 `N - 1`번 철학자와  `N + 1`번 철학자 사이에 위치한다.
10. 출력이 뒤엉켜서는 안된다.
11. 철학자가 죽으면 `10ms`안에 출력해야 한다.

## philo_one
> thread, mutex

* 각 철학자 사이에 1개의 포크가 있으며, 철학자의 왼쪽과 오른쪽에 위치한다.  
* 포크의 상태를 `mutex`로 보호한다.  
* 각 철학자는 `thread`이다.

### 허용 함수
```c
void	*memset(void *b, int c, size_t len);
int		printf(const char * restrict format, ...);
void	*malloc(size_t size);
void	free(void *ptr);
ssize_t	write(int fildes, const void *buf, size_t nbyte);
int		usleep(useconds_t microseconds);
int		gettimeofday(struct timeval *restrict tp, void *restrict tzp);
int		pthread_create(pthread_t *thread, const pthread_attr_t *attr, void *(*start_routine)(void *), void *arg);
int		pthread_detach(pthread_t thread);
int		pthread_join(pthread_t thread, void **value_ptr);
int		pthread_mutex_init(pthread_mutex_t *mutex, const pthread_mutexattr_t *attr);
int		pthread_mutex_destroy(pthread_mutex_t *mutex);
int		pthread_mutex_lock(pthread_mutex_t *mutex);
int		pthread_mutex_unlock(pthread_mutex_t *mutex);
```









## philo_two
> 세마포어

### 허용 함수
```c
void	*memset(void *b, int c, size_t len);
int		printf(const char * restrict format, ...);
void	*malloc(size_t size);
void	free(void *ptr);
ssize_t	write(int fildes, const void *buf, size_t nbyte);
int		usleep(useconds_t microseconds);
int		gettimeofday(struct timeval *restrict tp, void *restrict tzp);
int		pthread_create(pthread_t *thread, const pthread_attr_t *attr, void *(*start_routine)(void *), void *arg);
int		pthread_detach(pthread_t thread);
int		pthread_join(pthread_t thread, void **value_ptr);
sem_t	*sem_open(const char *name, int oflag, ...);
int		sem_close(sem_t *sem);
int		sem_post(sem_t *sem);
int		sem_wait(sem_t *sem);
int		sem_unlink(const char *name);
```

## philo_three
> 프로세스 동기화
큐활용(?)

### 허용 함수
```c
void	*memset(void *b, int c, size_t len);
int		printf(const char * restrict format, ...);
void	*malloc(size_t size);
void	free(void *ptr);
ssize_t	write(int fildes, const void *buf, size_t nbyte);
pid_t	fork(void);
int		kill(pid_t pid, int sig);
void	exit(int status);
pid_t	waitpid(pid_t pid, int *stat_loc, int options);
int		usleep(useconds_t microseconds);
int		gettimeofday(struct timeval *restrict tp, void *restrict tzp);
int		pthread_create(pthread_t *thread, const pthread_attr_t *attr, void *(*start_routine)(void *), void *arg);
int		pthread_detach(pthread_t thread);
int		pthread_join(pthread_t thread, void **value_ptr);
sem_t	*sem_open(const char *name, int oflag, ...);
int		sem_close(sem_t *sem);
int		sem_post(sem_t *sem);
int		sem_wait(sem_t *sem);
int		sem_unlink(const char *name);
```


## 용어 정리
1. Deadlock
2. Starvation
3. [스레드와 프로세스](https://namu.wiki/w/%EC%8A%A4%EB%A0%88%EB%93%9C#s-2.2.1)



