#ifndef PHILO_H
# define PHILO_H
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <sys/time.h>
# include <time.h>
# include <stdbool.h>

# define TAKEN		0
# define EAT		1
# define SLEEP		2
# define THINK		3
# define DIE		4

typedef struct	s_params {
	int					num;
	uint64_t			die;
	uint64_t			eat;
	uint64_t			sleep;
	int					number_eats;
	pthread_mutex_t		*stick;
	pthread_mutex_t		printer;
	pthread_t			*threads;
	uint64_t			ini_start;
	int					is_dead;
}						t_params;

typedef struct s_philosopher {
	int					id;
	pthread_mutex_t		*stick_l;
	pthread_mutex_t		*stick_r;
	pthread_mutex_t		*printer;
	t_params			params;
	uint64_t			*ini_start;
	uint64_t			last_eat;
	int					*is_dead;

}				t_philosopher;

int			arg_count(int argc);
int			handle_param(char *argv);
int			ft_isdigit(int c);
int			check_max_int(char *argv);
void		ini_threads(t_params *params, t_philosopher *philo);
int			ft_usleep(uint64_t time, t_philosopher *philo);
uint64_t	get_time(void );
void		*philo_routine(void *arg);
uint64_t	get_time_sub(uint64_t subtraction);


#endif
