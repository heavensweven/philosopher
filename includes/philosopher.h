/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rsalette <rsalette@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 15:14:24 by rsalette          #+#    #+#             */
/*   Updated: 2025/09/14 19:04:35 by rsalette         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include <string.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

typedef enum e_bool
{
	FALSE,
	TRUE
}						t_bool;

typedef enum e_state
{
	THINKING,
	EATING,
	SLEEPING,
}						t_state;

typedef struct s_fork
{
	int				fork_id;
	pthread_mutex_t	fork_mutex;
}			t_fork;

typedef struct s_data	t_data;

typedef struct s_philosopher
{
	int				philo_id;
	int				meal_count;
	long			last_meal;
	pthread_mutex_t	meal_data_mutex;
	t_fork			*left_fork;
	t_fork			*right_fork;
	t_state			state;
	pthread_t		th_philo;
	t_data			*data;
}						t_philo;

typedef struct s_param
{
	int				nb_philo;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				number_of_times_each_philosopher_must_eat;
}						t_param;

typedef struct s_watchdog_args
{
	t_data			*data;
	int				nb_philo;
	int				time_to_die;
	int				must_eat;
	int				full_philo_count;
}						t_watchdog_args;

struct s_data
{
	long			start_time;
	t_param			param;
	t_philo			*philo;
	t_bool			philo_alloc;
	t_fork			*fork;
	t_bool			fork_alloc;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	stop_mutex;
	t_bool			stop;
	char			error_string[256];
	pthread_t		th_watchdog;
};

/* main_process.c */
int				simulation(t_data *data);
int				threads_create(t_data *data);
int				threads_join(t_data *data);
int				main(int argc, char **argv);

/* init.c */
int				data_initializer(int argc, char **argv, t_data *data);
t_fork			create_fork(int number);
int				fork_initializer(t_data *data);
t_philo			create_philo(int number, t_data *data);
int				philo_initializer(t_data *data);

/* error_and_close_management_0.c */
void			free_philo(t_data *data);
void			free_fork(t_data *data);
void			memory_liberator(t_data *data);
void			free_args(char **tab);
void			error_print(char *str);

/* error_and_close_management_1.c */
void			free_tab(char **tab);
void			*free_tab_partial(char **tab, int n);

/* forking.c */
int				fork_holding(t_philo *philo);
void			unlock_forks(t_philo *philo);

/* parsing.c */
int				arg_management(int argc, char **argv, t_data *data);
char			**arg_setter(int argc, char **argv);
int				mandatory_arg_dispatch(t_data *data, char	**args);
int				optional_arg_dispatch(t_data *data, char	**args);
int				arg_check(char **args);

/* time_management.c */
long			get_time_from_start(long start_time);
long			get_current_time(void);

/* threads.c */
void			*watchdog_thread_ft(void *arg);
int				watchdog_check_loop(t_watchdog_args	*wd_args);
void			*philo_thread_ft(void *arg);

/* routines_0.c */
int				eating(t_philo *philo);
int				sleeping(t_philo *philo);
int				thinking(t_philo *philo);
int				default_philo_routine(t_philo *philo);

/* controls.c */
int				death_management(t_philo *philo, int time_to_die);
int				check_stop(t_philo *philo);
int				eat_limit_management(t_philo *philo, t_watchdog_args *wd_args);

/* printing.c */
void			print_state(t_philo *philo);
void			print_fork(t_philo *philo);
void			print_death(t_philo *philo);

/* utils_0.c */
int				smart_usleep(t_philo *philo, int duration);
int				ft_tablen(char **tab);
size_t			ft_abs(size_t m);
size_t			ft_min(size_t n1, size_t n2);
int				ft_isdigit(int c);

/* utils_1.c */
char			*ft_strdup(const char *s);
void			*ft_calloc(size_t nmemb, size_t size);
size_t			ft_strlen_ultimate(const char *str);
size_t			ft_strlcat(char *dst, const char *src, size_t siz);
char			*ft_substr(char const *s, unsigned int start, size_t len);

/* ft_split.c */
unsigned int	ft_countsplit(char const *string, char const find);
unsigned int	ft_splitlen(char const *string, char const find);
void			ft_antileak(char **arr, int row);
char			*ft_get_next_word(char const *s, char c, int *i);
char			**ft_split(char const *s, char c);

/* ft_atoi.c */
int				ft_atoi(const char *ptr);

#endif